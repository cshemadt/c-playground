#include "stack.h"
struct int_array create_int_array(size_t sz) {
	return (struct int_array) {
		.data = (int64_t *) malloc(sizeof(int64_t)*sz),
		.size=sz
	};
}
size_t stack_count(struct stack *s) { return s->curr_stack_pos; }
struct stack stack_create(size_t sz) {
	return (struct stack) {.data = create_int_array(sz), .curr_stack_pos = 0};
}
void stack_destroy(struct stack *s) {
	free(s->data.data);
	s->curr_stack_pos = 0;
}
bool is_stack_full(struct stack *s) { return s->curr_stack_pos == s->data.size; }
bool is_stack_empty(struct stack *s) { return s->curr_stack_pos == 0; }
int64_t pop(struct stack *s) {
	if(!is_stack_empty(s))
		return s->data.data[--(s->curr_stack_pos)];
	else
		printf("Stack is empty\n");
	return -1;
}
bool push(struct stack *s, int64_t value) {
	if(!is_stack_full(s)) {
		s->data.data[s->curr_stack_pos++] = value;
		return true;
	}
	printf("Stack is full\n");
	return false;
}
void print_stack(struct stack *s) {
	for(size_t i=0;i<s->curr_stack_pos;printf("%" PRId64 " ", s->data.data[i++])) ;
}
