/**
 * @brief single linked list interface file
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "slist.h"

/*
 * Internal functions
 */

/**
 * @brief makes a link of a outside incoming item to a list
 */
static void slist_link(slist_info_t *s, slist_t *item)
{
	/* in order to ensure O(1) insertion
	 * only does a prepend in target list
	 */
	item->next = s->first;
	s->first->prev = item;
	s->first = item;
	item->prev = NULL;
	s->noof_elements++;
}

/**
 * @brief breaks the link of specified list item
 */
static void slist_unlink(slist_info_t *s, slist_t *item)
{
	if(item != NULL) {
		if(s->noof_elements == 1) {
			s->first = NULL;	
		} else {
			if(item->prev == NULL) {
				/* first item */
				s->first = s->first->next;
			} else {
				item->prev->next = item->next;
			}

			if(item->next != NULL) {
				/* not last item, so we have a next node*/
				item->next->prev = item->prev;
			} else {
				item->prev->next = NULL;
			}
		}

		if(s->noof_elements > 0)
			s->noof_elements--;
	}
}


/*
 *  Public functions
 */

int slist_insert(slist_info_t *s, slist_t *item, void *data)
{
	int ret = 0;
	uint8_t *ptr = data;

	/* check arguments */
	if((s == NULL) || (item == NULL) || (data == NULL)) {
		ret = -1;
	} else {

		item->data = data;

		/* is the first element? */
		if(s->noof_elements == 0) {
			/* links the new element directly */
			item->next = NULL;
			item->prev = NULL;
			s->first = item;
			s->noof_elements++;
		} else {
			/* prepend the new element on list */
			slist_link(s, item);
		}
	}
	return (ret);
}

int slist_get_noof_entries(slist_info_t *s)
{
	int ret = 0;
	/* check arguments */
	if(s == NULL) {
		ret = -1;
	}else {
		ret = s->noof_elements;
	}
	return(ret);
}

void* slist_get_data_when_true(slist_info_t *s, void *ctx,
		int (*condition)(const void *data, void *ctx))
{
	void *ret = NULL;	

	/* check arguments */
	if((s == NULL)) {
		return NULL;
	}

	slist_t *tmp = s->first;
	while(tmp != NULL && !condition(tmp->data, ctx)) {
		tmp = tmp->next;
	}

	if(tmp != NULL) {
		/* found data */
		ret = tmp->data;
	}
	return ret;
}

slist_t *slist_get_slot_when_true(slist_info_t *s, void *ctx,
		int (*condition)(const void *data, void *ctx),
		bool remove)
{
	slist_t *ret = NULL;	

	/* check arguments */
	if((s == NULL)) {
		return NULL;
	}

	slist_t *tmp = s->first;
	while(tmp != NULL && !condition(tmp->data, ctx)) {
		tmp = tmp->next;
	}

	if(tmp != NULL) {
		/* found data */
		ret = tmp;

		if(remove != false) {
			slist_unlink(s,tmp);
		}
	}
	return ret;
}

void print_list(slist_info_t *s,
				void (*print_func)(uint8_t *data))
{
	slist_t *tmp = s->first;
	while(tmp != NULL) {
		print_func(tmp->data);
		tmp = tmp->next;
	}
}
