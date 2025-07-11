#include "slist.h"
#include <iostream>
#include <stdint.h>
#include <stdlib.h>

// TODO: Sprinkle the code with asserts

slist_node_t *slist_node(int val) {
	slist_node_t *node = calloc(1, sizeof(slist_node_t));
	if (node == NULL) {
		return NULL;
	}
	node -> next = NULL;
	node -> val = val;
	return node;
}

void slist_node_deinit(slist_node_t *node) {
	free(node);
	return;
}

slist_t slist_init() {
	return (slist_t) {
		.head = NULL,
		.tail = NULL
	};
}

void slist_deinit(slist_t *list) {
	slist_node_t *node = list -> head;
	while (node != NULL) {
		slist_node_t *temp = node -> next;
		free(node);
		node = temp;
	}
}

uint64_t slist_size(slist_t list) {
	uint64_t count = 0;
	slist_node_t *head = list.head;
	while (head != NULL) {
		count++;
		head = head -> next;
	}
	return count;
}

bool slist_empty(slist_t list) {
	return list.head == list.tail && list.head == NULL;
}

val_result_t slist_get(slist_t list, uint64_t idx) {
	uint64_t cnt = 0;
	slist_node_t *head = list.head;
	while (head != NULL && cnt != idx) {
		head = head -> next;
		cnt++;
	}
	bool cond = head != NULL;
	return (val_result_t) {
		.err = cond ? NONE : OUT_OF_BOUNDS,
		.val = cond ? head -> val : 0,
	};
}

val_result_t slist_get_from_tail(slist_t list, uint64_t idx) {
	uint64_t cnt = 0;
	slist_node_t *fast = list.head; 
	slist_node_t *slow = list.head;

	while (fast != NULL && cnt != idx) {
		fast = fast -> next;
		cnt++;
	}
}

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
