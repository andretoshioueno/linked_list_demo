/**
 * @brief single linked list interface file
 */

#ifndef __SLIST_H_
#define __SLIST_H_

#include <stdbool.h>
#include <stdint.h>

/* single linked list data structure */
typedef struct slist_s {
	void *data;
	struct slist_s *next;
	struct slist_s *prev;
}slist_t;

/* single linked list head data structure */
typedef struct {
	slist_t *first;
	int noof_elements;
}slist_info_t;


/**
 * @brief insert an container in the slist
 */
int slist_insert(slist_info_t *s, slist_t *item, void *data);

/**
 * @brief deletes all the items in current list
 */
int slist_clean(slist_info_t *s);

/**
 * @brief get the current number of entries on list
 */
int slist_get_noof_entries(slist_info_t *s);

/**
 * @brief gets data when a certain condition is met
 */
void *slist_get_data_when_true(slist_info_t *s, void *ctx,
		int (*condition)(const void *data, void *ctx));

/**
 * @brief gets slot when a certain condition is met with optional removeal
 * Get data pointer first with slist_get_data_when_true and free it to avoid
 * memory leak
 */
slist_t *slist_get_slot_when_true(slist_info_t *s, void *ctx,
		int (*condition)(const void *data, void *ctx),
		bool remove);

void print_list(slist_info_t *s,
				void (*print_func)(uint8_t *data));



/**
 * @brief linked list instantiation macro:
 */
#define SLIST_DECLARE(name)			\
		slist_info_t name = {		\
			.first = (void *)0,		\
			.noof_elements = 0,		\
		}							\


#endif /* SLIST_H_ */
