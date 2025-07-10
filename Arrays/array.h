#ifndef BAKAGEDDY_ARRAY_H
#define BAKAGEDDY_ARRAY_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
	int *data;
	uint64_t capacity;
	uint64_t len;
} array_t;

typedef enum {
	NONE,
	EMPTY,
	NOT_FOUND,
	OUT_OF_MEMORY
} err_t;

typedef struct pop_result_t {
	err_t err = NONE;
	int data;
} pop_result_t;

typedef struct find_result_t {
	err_t err = NONE;
	uint64_t data;
} find_result_t;

array_t *init_array();
array_t *init_array_with_cap(uint64_t);
uint64_t array_len(array_t *);
uint64_t array_cap(array_t *);
bool array_is_empty(array_t *); 

int array_get(array_t *, uint64_t);
err_t array_push(array_t *, int);
err_t array_insert(array_t *, uint64_t, int);
err_t array_prepend(array_t *, int);
pop_result_t array_pop(array_t *);
int array_delete(array_t *, uint64_t);
void array_remove_left(array_t *, int);
void array_remove_right(array_t *, int);
void array_remove_all(array_t *, int);
find_result_t array_find(array_t *, int);
err_t array_resize(array_t *);

void deinit_array(array_t *);

#endif // BAKAGEDDY_ARRAY_H
