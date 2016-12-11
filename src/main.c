/**
 * @brief main application file
 */
#include <stdio.h>
#include <stdlib.h>
#include "slist.h"

SLIST_DECLARE(test_list);


/**
 * @brief main function loop
 */
int main (int argc, char **argv)
{
	for (int i = 1; i < 64; i ++) {
		slist_t *slot = malloc(sizeof(slist_t));
		int *data = malloc(sizeof(int));
		*data = i;
		if(slist_insert(&test_list, slot, data) == 0 ) {
			int int_data = 0;
			slist_get_data_from_tail(&test_list, &int_data, false);
			printf("current tail of list is: %d \n\r", int_data);
		}else {
			printf("error inserting data on list \n\r");
		}
	}
	return 0;
}
