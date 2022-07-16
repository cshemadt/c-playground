#include "stack.h"
struct maybe_i64 some_i64(int64_t v) { return (struct maybe_i64) {.valid = true, .value = v}; };
struct maybe_i64 read_int64() {
	int64_t i;
	return (scanf("%" SCNd64,&i)==1) ? some_i64(i) : none_i64;
}
const size_t STACK_CAPACITY = 100;
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
struct maybe_i64 pop(struct stack *s) {
	if(!is_stack_empty(s))
		return some_i64(s->data.data[--(s->curr_stack_pos)]);
	else
		printf("Stack is empty\n");
	return none_i64;
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
	printf("\n");
}
