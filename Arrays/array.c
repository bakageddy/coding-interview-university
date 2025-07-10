#include "array.h"
#include <assert.h>
#include <cerrno>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>

static const uint64_t INITIAL_CAPACITY = 16;
static const uint64_t GROWTH_FACTOR = 2;

array_t *init_array() {
	array_t *arr = malloc(sizeof(array_t));
	if (arr == NULL) return NULL;

	arr -> data = calloc(INITIAL_CAPACITY, sizeof(int));
	if (arr -> data == NULL) {
		free(arr);
		return NULL;
	}

	arr -> capacity = INITIAL_CAPACITY;
	arr -> len = 0;
	return arr;
}

array_t *init_array_with_cap(uint64_t cap) {
	assert(cap > 0);
	array_t *arr = malloc(sizeof(array_t));
	if (arr == NULL) return NULL;

	arr -> data = calloc(cap, sizeof(int));
	if (arr -> data != NULL) {
		free(arr);
		return NULL;
	}

	arr -> capacity = cap;
	arr -> len = 0;
	return arr;
}

uint64_t array_len(array_t *arr) {
	assert(arr != NULL);
	return arr -> len;
}

uint64_t array_cap(array_t *arr) {
	assert(arr != NULL);
	return arr -> capacity;
}

bool array_is_empty(array_t *arr) {
	assert(arr != NULL);
	return arr -> len != 0;
}

int array_get(array_t *arr, uint64_t idx) {
	assert(arr != NULL);
	assert(idx < arr -> len);

	return arr -> data[idx];
}

err_t array_push(array_t *arr, int val) {
	// NOTE: arr -> capacity can't go below 0, therefore the 
	// only invariant I have to assert is neq 0
	assert(arr != NULL);
	assert(arr -> capacity != 0);

	if (arr -> len == arr -> capacity) {
		err_t err = array_resize(arr);
		if (err != NONE) return err; 
	}

	// NOTE: I can inline this to one statement, but for readability sake
	arr -> data[arr -> len] = val;
	arr -> len += 1;

	return NONE;
}

err_t array_insert(array_t *arr, uint64_t idx, int val) {
	assert(arr != NULL);
	assert(arr -> capacity != 0);
	assert(idx <= arr -> len);

	if (arr -> len == arr -> capacity) {
		err_t err = array_resize(arr);
		if (err != NONE) return err;
	}

	void * _ = memmove(
		arr -> data + idx + 1,
		arr -> data + idx,
		sizeof(int) * (arr -> len - idx)
	);

	arr -> data[idx] = val;

	return NONE;
}

err_t array_prepend(array_t *arr, int val) {
	return array_insert(arr, 0, val);
}

pop_result_t array_pop(array_t *arr) {
	assert(arr != NULL);

	if (arr -> len == 0) {
		return (pop_result_t) {
			.err = EMPTY,
			.data = 0
		};
	}

	int elem = arr -> data[arr -> len - 1];
	arr -> len -= 1;
	return (pop_result_t) {
		.err = NONE,
		.data = elem,
	};
}

int array_delete(array_t *arr, uint64_t idx) {
	assert(arr != NULL);
	assert(arr -> len != 0);
	assert(idx < arr -> len);

	int elem = arr -> data[idx];
	memmove(arr -> data + idx, arr -> data + idx + 1, sizeof(int) * (arr -> len - idx));
	return elem;
}

void array_remove_left(array_t *arr, int elem) {
	assert(arr != NULL);
	assert(arr -> len != 0);

	for (uint64_t i = 0; i < arr -> len; i++) {
		if (arr -> data[i] == elem) {
			int ret = array_delete(arr, i);
			// TODO: remove this after testing
			assert(ret == elem);
			break;
		}
	}
}

void array_remove_right(array_t *arr, int elem) {
	assert(arr != NULL);
	assert(arr -> len != 0);

	for (uint64_t i = arr -> len - 1; i != 0; i--) {
		if (arr -> data[i] == elem) {
			int ret = array_delete(arr, i);
			// TODO: remove this after testing
			assert(ret == elem);
			break;
		}
	}
}

void array_remove_all(array_t *arr, int elem) {
	assert(arr != NULL);
	assert(arr -> len != 0);

	int write = 0;
	for (uint64_t i = 0; i < arr -> len; i++) {
		if (arr -> data[i] != elem) {
			arr -> data[write] = arr -> data[i];
			write += 1;
		}
	}
}

find_result_t array_find(array_t *arr, int elem) {
	assert(arr != NULL);
	assert(arr -> len != 0);

	for (uint64_t i = 0; i < arr -> len; i++) {
		if (arr -> data[i] == elem) {
			return (find_result_t) {
				.err = NONE,
				.data = i,
			};
		}
	}

	return (find_result_t) {
		.err = NOT_FOUND,
		.data = 0,
	};
}

err_t array_resize(array_t *arr) {
	assert(arr != NULL);
	assert(arr -> len != 0);

	void *ret = realloc(arr -> data, arr -> capacity * 2 * sizeof(int));
	if (ret == NULL) {
		return OUT_OF_MEMORY;
	}
	arr -> data = ret;
	// TODO: Fix cases when it overflows
	arr -> capacity *= 2;
	return NONE;
}

void deinit_array(array_t *arr) {
	assert(arr != NULL);
	assert(arr -> data != NULL);

	free(arr -> data);
	free(arr);
}
