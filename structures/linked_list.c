#include <stdio.h>
#include <math.h>
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

void print_node(i64 i) { printf("%" PRId64 " ", i); }
void list_foreach(const struct node* head, void (f) (i64)) {
	while(head) {
		f(head->value);
		head=head->next;
	}
	printf("\n");
}
void print_list(struct node* head) {
	if(!head) {
		printf("List is empty!\n");
		return;
	}
	while(head) {
		printf("%" PRId64 " ", head->value);
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
void list_map_mut(struct node *head, i64 (f) (i64)) {
	while(head) {
		head->value=f(head->value);
		head=head->next;
	}
}
static i64 triple(i64 x) { return x*3; }
static i64 node_value(i64 x) { return x; }
static i64 node_abs(i64 x) { return abs(x); }
void list_triple(struct node *head) {
	list_map_mut(head, triple);
}
struct node* list_map( const struct node* head, int64_t (f) (int64_t))  {
    struct node *newhead=NULL;
    while(head) {
        struct node *node=node_create(f(head->value));
		if(!newhead)
			newhead=node;
		else
			list_last_node(newhead)->next = node;
		head=head->next;
    }
	return newhead;
}
struct node* list_copy( const struct node *head ) {
    return list_map(head, node_value);
}
struct node* list_abs( const struct node  *head ) {
    return list_map(head, node_abs);
}
struct node* list_iterate( int64_t init, size_t sz, int64_t(f)(int64_t)) {
	struct node *head = (sz>0) ? node_create(init) : NULL;
	for(size_t i=1;i<sz;i++) {
		struct node *last = list_last_node(head);
		struct node *node = node_create(f(last->value));
		last->next=node;
	}
	return head;
}
int main(void) {
	struct node *head=NULL;
	push_back(&head, 1);
	push_back(&head, 3); 
	push_back(&head, 4); 
	push_back(&head, 6); 
	/* two ways to print the linked list */
	/* print_list(head); */
	struct node *iterated_list = list_iterate(10,100,triple);
	list_foreach(iterated_list, print_node);
}
