/**
 * @brief single linked list interface file
 */

#ifndef __SLIST_H_
#define __SLIST_H_

#include <stdbool.h>

/* single linked list data structure */
typedef struct slist_s {
	void *data;
	struct slist_s *next;
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
 * @brief gets data from a specified position with optional remotion
 */
int slist_get_data_from_position(slist_info_t *s, int position,  void *data, bool remove);


/**
 * @brief gets data from head with optional remotion
 */
int slist_get_data_from_head(slist_info_t *s, void *data, bool remove);


/**
 * @brief gets data from tail with optional remotion
 */
int slist_get_data_from_tail(slist_info_t *s,  void *data, bool remove);


/**
 * @brief deletes all the items in current list
 */
int slist_clean(slist_info_t *s);

/**
 * @brief get the current number of entries on list
 */
int slist_get_noof_entries(slist_info_t *s);


/**
 * @brief linked list instantiation macro:
 */
#define SLIST_DECLARE(name)			\
		slist_info_t name = {		\
			.first = (void *)0,		\
			.noof_elements = 0,		\
		}							\


#endif /* SLIST_H_ */
