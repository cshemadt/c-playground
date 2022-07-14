#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
struct int_array { int64_t *data; size_t size; };
struct int_array create_int_array(size_t sz);
struct stack {
	size_t curr_stack_pos;
	struct int_array data;
};
size_t stack_count(struct stack *s);
struct stack stack_create(size_t sz);
void stack_destroy(struct stack *s);
bool is_stack_full(struct stack *s);
bool is_stack_empty(struct stack *s);
void print_stack(struct stack *s);
int64_t pop(struct stack *s);
bool push(struct stack *s, int64_t value);
