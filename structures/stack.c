#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
struct node {
	int64_t value;
	struct node* next;
};
struct node* node_create(int64_t value) {
	struct node* new_node = malloc(sizeof(struct node));
	new_node->value=value;
	new_node->next=NULL;
	return new_node;
}
void l_list_print() {
} 
void add_node_front(struct node* old, int64_t value) {
	struct node* new_node = node_create(value);
	new_node->next = old;
	old->next = NULL;
}
int main(void) {
	struct node* node = node_create(15);
	/*node_print(node);*/
	add_node_front(node, 20);
	return 0;
}
