#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
struct node {
	int64_t value;
	struct node *next;
};
void print_int64(int64_t i) { printf("%" PRId64 " ", i); }
void list_foreach(const struct node *head, void (f) (int64_t)) {
	while(head) {
		f(head->value);
		head=head->next;
	}
}
void list_print(const struct node *head) {
	list_foreach(head, print_int64);
}
int main(void) {
	struct node n3 = {3,NULL};
	struct node n2 = {2,&n3};
	struct node n1 = {1,&n2};
	list_foreach(&n1, print_int64);
	return 0;
}
