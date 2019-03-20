/**
 * @brief main application file
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "slist.h"

SLIST_DECLARE(test_list);
SLIST_DECLARE(test_list2);

struct poster {
		uint8_t name[30];
} poster;

void print_func(uint8_t *name) {
	printf("name found = %s\n", name);
}

int isPosterName(const void *data, void *ctx) {
	poster_data *poster_data = ctx;
	const uint8_t *name = data;

	printf("name found = %s, requested_name  %s\n", name, poster_data->name);

	return (strcmp(name, poster_data->name) == 0);
}

void addItem(uint8_t *poster_name)
{
	slist_t *slot = malloc(sizeof(slist_t));
	struct poster *data = calloc(1, sizeof(struct poster));
	strcpy(data->name, poster_name);

	printf("poster to add: %s\n", data->name);

	if(slist_insert(&test_list2, slot, data) != 0 ) {
		printf("ERROR insert\n");
	}
}

void getData(uint8_t *poster_name)
{
	uint8_t *name;
	slist_t *slot;

	name = slist_get_data_when_true(&poster_list,
								poster_name,
								isPosterName);

	slot = slist_get_slot_when_true(&test_list2,
								poster_name,
								isPosterName,
								true);

	if(name != NULL) {
		printf("Found!!! = %s\n", name);
		free(name);
		free(slot);
	} else {
		printf("could not find poster %s\n", name);
	}

}

void mytest()
{
	addItem("POSTER1");
	addItem("POSTER2");
	addItem("POSTER3");
	addItem("POSTER4");
	addItem("POSTER5");

	printf("Resulting list:\n");
	print_list(&test_list2, print_func);

	getData("POSTER1");
	printf("Resulting list:\n");
	print_list(&test_list2, print_func);
	printf("\n\n");

	getData("POSTER1");
	printf("Resulting list:\n");
	print_list(&test_list2, print_func);
	printf("\n\n");

	getData("POSTER1");
	printf("Resulting list:\n");
	print_list(&test_list2, print_func);
	printf("\n\n");

	getData("POSTER1");
	printf("Resulting list:\n");
	print_list(&test_list2, print_func);
	printf("\n\n");

	getData("POSTER1");
	printf("Resulting list:\n");
	print_list(&test_list2, print_func);
	printf("\n\n");

}


/**
 * @brief main function loop
 */
int main (int argc, char **argv)
{
	mytest();
}
