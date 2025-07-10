#include "array.h"
#include <stdint.h>
#include <stdlib.h>

static const uint64_t INITIAL_CAPACITY = 16;

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
	array_t *arr = malloc(sizeof(array_t));
}
uint64_t array_len(array_t *);
uint64_t array_cap(array_t *);
bool array_is_empty(array_t *); 

int array_get(array_t *, uint64_t);
err_t array_push(array_t *, int);
err_t array_insert(array_t *, uint64_t, int);
err_t array_prepend(array_t *, int);
int array_pop(array_t *);
int array_delete(array_t *, uint64_t);
void array_remove_left(array_t *, int);
void array_remove_right(array_t *, int);
void array_remove_all(array_t *, int);
find_result_t array_find(array_t *, int);
err_t array_resize(array_t *);

void *deinit_array(array_t *);
