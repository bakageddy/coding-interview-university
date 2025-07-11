#ifndef BAKAGEDDY_LIST_H
#define BAKAGEDDY_LIST_H

#include <stdbool.h>
#include <stdint.h>

typedef struct slist_node_t {
	int val;
	slist_node_t *next;
} slist_node_t;

typedef struct slist_t {
	slist_node_t *head;
	slist_node_t *tail;
} slist_t;

typedef enum {
	NONE,
	OUT_OF_BOUNDS
} err_t;

typedef struct {
	err_t err;
	int val;
} val_result_t; // should be val_result_t

typedef struct {
	err_t err;
	uint64_t val;
} idx_result_t;

slist_node_t *slist_node(int);
void slist_node_deinit(slist_node_t *);
slist_t slist_init();
void slist_deinit(slist_t *);

uint64_t slist_size(slist_t);
bool slist_empty(slist_t);
val_result_t slist_get(slist_t, uint64_t);
val_result_t slist_get_from_tail(slist_t, uint64_t);

int slist_head(slist_t);
int slist_tail(slist_t);

err_t slist_push(slist_t *, int);
err_t slist_push_node(slist_t *, slist_node_t *);

err_t slist_prepend(slist_t *, int);
err_t slist_prepend_node(slist_t *, slist_node_t *);

val_result_t slist_pop(slist_t *);
val_result_t slist_pop_front(slist_t *);

err_t slist_insert(slist_t, uint64_t, int);
err_t slist_insert_node(slist_t, uint64_t, slist_node_t *);

int slist_delete(slist_t *, uint64_t);
int slist_remove(slist_t *, int);
int slist_remove_node(slist_t *, slist_node_t *);

int slist_reverse(slist_t *);

#endif // BAKAGEDDY_LIST_H
