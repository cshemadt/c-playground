#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
struct node {
	int64_t value;
	struct node* next;
};
void node_print(struct node* node) {
	printf("%" PRId64, node->value);
}
struct node* node_create(int64_t value) {
	struct node* new_node = malloc(sizeof(struct node));
	new_node->value=value;
	new_node->next=NULL;
	return new_node;
}
int main(void) {
	struct node* node = node_create(15);
	node_print(node);
	return 0;
}
