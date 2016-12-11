/**
 * @brief single linked list interface file
 */

#include <string.h>
#include <stdlib.h>
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
	item->next = s->first->next;
	s->first = item;
	s->noof_elements++;
}

/**
 * @brief breaks the link of specified list item
 */
static void slist_unlink(slist_info_t *s, slist_t *item, int position)
{
	/*
	 * WARN: when using unlink by item, make sure the desired item to
	 *  	unlink is the next linked to the item argument
	 */

	/* check how to link */
	if(item != NULL) {
		/* item based, remove the next entrie, this the desired
		 * entry to unlink and not the current item
		 */
		slist_t *tmp = item->next;
		item->next = tmp->next;
		tmp->next = NULL;
		if(s->noof_elements > 0) s->noof_elements--;

	} else if (position != 0) {
		/*
		 * TODO: position based is used only in special case,
		 * 	     when the list has only 1 position, so if needed in future
		 * 	     implement to handle all the list using position based
		 * 	     remotion
		 */
		if(s->noof_elements > 1) {
			slist_t *tmp = s->first;
			s->first = tmp->next;
			tmp->next = NULL;
			if(s->noof_elements > 0) s->noof_elements--;

		}else {
			s->first = NULL;
			s->noof_elements = 0;
		}
	}

}


/*
 *  Public functions
 */

int slist_insert(slist_info_t *s, slist_t *item, void *data)
{
	int ret = 0;

	/* check arguments */
	if((s == NULL) || (item == NULL) || (data == NULL)) {
		ret = -1;
	} else {

		/* is the first element? */
		if(s->noof_elements == 0) {
			/* links the new element directly */
			item->data = data;
			item->next = NULL;
			s->first = item;
			s->noof_elements++;
		} else {
			item->data = data;
			item->next = NULL;
			/* prepend the new element on list */
			slist_link(s, item);
		}
	}
	return (ret);
}



int slist_get_data_from_position(slist_info_t *s, int position,  void *data, bool remove)
{
	int ret = 0;

	/* check arguments */
	if((s == NULL) || (position == 0)) {
		ret = -1;
	} else {
		/* check if position exists */
		if(position <= s->noof_elements) {
			/* list has only 1 position? */
			if(s->noof_elements == 1) {
				data = s->first->data;
				/* if needs unlink */
				if(remove != false) {
					slist_unlink(s,NULL, position);
				}
			} else {
				/* find the index where the data is located */
				slist_t *tmp = s->first;
				for(int i = 1; i != position -1 ; tmp = tmp->next, i++);
				data = tmp->data;

				/* unlink if needed */
				if(remove != false) {
					slist_unlink(s,tmp, 0);
				}
			}

		} else {
			ret = -1;
		}

	}
	return(ret);
}

int slist_get_data_from_head(slist_info_t *s, void *data, bool remove)
{
	int ret = 0;

	/* check arguments */
	if((s == NULL)) {
		ret = -1;
	} else {

		if(s->noof_elements != 0) {
			/* we want the head of list, so the first item
			 * added in the list, which is located at end of it
			 */
			int position = s->noof_elements;
			slist_t *tmp = s->first;
			for(int i = 1; i != position -1 ; tmp = tmp->next, i++);
			data = tmp->data;

			/* unlink if needed */
			if(remove != false) {
				slist_unlink(s,tmp, 0);
			}
		} else {
			/* list is empty */
			ret = -1;
		}
	}
	return(ret);

}

int slist_get_data_from_tail(slist_info_t *s,  void *data, bool remove)
{
	int ret = 0;

	/* check arguments */
	if((s == NULL)) {
		ret = -1;
	} else {
		/* we want the tail of list, so the last item
		 * added in the list, which is located at beginning of it
		 */
		data = s->first->data;

		/* unlink if needed */
		if(remove != false) {
			slist_unlink(s,NULL, 1);
		}
	}
	return(ret);

}

int slist_clean(slist_info_t *s)
{
	int ret = 0;

	/* check arguments */
	if(s == NULL) {
		ret = -1;
	} else {
		int position = s->noof_elements;
		slist_t *tmp = s->first;

		/* unlink the items chain from root of the list */
		s->first = NULL;
		s->noof_elements = 0;

		/* unlink the further slots */
		for(int i = 1; i != position - 1; i++) {
			slist_t *unlink = tmp->next;
			tmp->next = NULL;
			tmp = unlink;
		}

	}
	return(ret);
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
