#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
typedef int64_t i64;
struct node {
	i64 value;
	struct node* next;
};

struct maybe_int64 {
	bool valid;
	i64 value;
};
struct maybe_int64 some_int64(i64 value) { return (struct maybe_int64) {.value=value, .valid=true}; }
const struct maybe_int64 none_int64 = {0}; 

void print_list(struct node* head) {
	if(!head) {
		printf("List is empty!\n");
		return;
	}
	printf("Linked list: ");
	while(head) {
		printf("% " PRId64, head->value);
		head=head->next;
	}
	printf("\n");
}
size_t list_length(const struct node* head) {
	size_t i;
	for(i=0;head;head=head->next,++i) ;
	return i;
}
void list_destroy(struct node* head) {
	while(head) {
		struct node* buff=head->next;
		free(head);
		head=buff;
	}
}
struct node* list_last_node(struct node* head) {
	while(head && head->next)
		head=head->next;
	return head;
}
struct node* node_create(i64 value) {
	struct node* new_node = malloc(sizeof(struct node));
	new_node->value=value;
	new_node->next=NULL;
	return new_node;
};
void push_front(struct node** head, i64 value) {
	struct node* node = node_create(value);
	if(*head) {
		node->next=*head;
		*head=node;
	}
	else
		*head=node;
}
void push_back(struct node** head, i64 value) {
	if(!(*head))
		push_front(head, value);
	else
		list_last_node(*head)->next=node_create(value);
}
i64 list_sum(const struct node* head) {
	i64 sum;
	for(sum=0;head;sum+=head->value,head=head->next) ;
	return sum;
}
struct maybe_int64 list_at(const struct node* head, size_t idx) {
	size_t i=0;
	if(idx >= list_length(head) || idx < 0 || !head)
	{
		printf("Not a number, exit.\n");
		return none_int64;
	}
	while(head) {
		if((i++)==idx) 
			return some_int64(head->value);
		head=head->next;
	}
	return none_int64;
}
struct node* list_reverse(const struct node* head) {
	struct node* new_head=NULL;
	while(head) {
		push_front(&new_head, head->value);
		head=head->next;
	}
	return new_head;
}
struct maybe_int64 maybe_read_int64() {
	i64 val;
	return (scanf("%" SCNd64, &val)>0) ? some_int64(val) : none_int64;
}
struct node* read_list() {
	struct node* head=NULL;
	struct maybe_int64 val=maybe_read_int64();
	do {
		push_back(&head, val.value);
	}
	while((val=maybe_read_int64()).valid);
	return head;
}
int main(void) {
	struct node* head = node_create(10);
	push_front(&head, 9);
	push_front(&head, 8);
	push_front(&head, 7);
	push_front(&head, 6);
	print_list(head);
	struct node* reversed_list_head = list_reverse(head);
	printf("Reversed ");
	print_list(reversed_list_head);
	printf("List length %zu\n", list_length(head));
	struct node* last_node=list_last_node(head);
	printf( "Last node: %" PRId64 "\n", last_node->value);
	printf("Sum of list: %" PRId64 "\n", list_sum(head));
	size_t idx=3;
	struct maybe_int64 n_el_of_list = list_at(head,idx);
	if(n_el_of_list.valid)
		printf("Element with index %zu is " "%" PRId64 "\n",idx,n_el_of_list.value);
	struct node* input_list_head = read_list();
	print_list(input_list_head);
	printf("%" PRId64, input_list_head->next->value);
}
