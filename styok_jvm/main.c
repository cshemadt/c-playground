#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "stack.c"
enum opcode {
	BC_PUSH, BC_POP, BC_SWAP, BC_DUB,
	BC_IADD, BC_ISUB, BC_IMUL, BC_IDIV,		
	BC_INEG,								
	BC_IPRINT, BC_IREAD,					
	BC_ICMP,
	BC_STOP
};
struct bc_noarg { enum opcode opcode; };
struct bc_arg64 { enum opcode opcode; int64_t arg; };
union ins {
	enum opcode opcode;
	struct bc_noarg as_bc_noarg;
	struct bc_arg64 as_bc_arg64;
};
struct vm_state {
	const union ins *ip;
	struct stack data_stack;
};
struct vm_state vm_state_create(union ins *ip) { return (struct vm_state) { .ip = ip, .data_stack = stack_create(STACK_CAPACITY) }; }
void vm_state_destroy(struct vm_state *vm) {
	vm->data_stack.curr_stack_pos=0;
	vm->ip=NULL;

	free(vm->data_stack.data.data);
}
/* TODO:
 * - maybe_i64 tests
 */
union ins program[] = {
	{BC_IREAD},
	{BC_IREAD},
	{BC_IREAD},
	{BC_IDIV},
	{BC_SWAP},
    {BC_STOP}
};
/* TODO: Move it to header file */
void interpret_push(struct vm_state* state);
void interpret_iread(struct vm_state* state );
void interpret_iprint(struct vm_state *state );
void interpret_stop(struct vm_state *state );

void interpret_ipop(struct vm_state *state);
void interpret_idup(struct vm_state *state);
void interpret_icmp(struct vm_state *state);

void interpret_iadd(struct vm_state *state);
void interpret_imul(struct vm_state *state);
void interpret_idiv(struct vm_state *state);
void interpret_isub(struct vm_state *state);
void interpret_iswp(struct vm_state *state);

void lift_unop(struct stack *s, int64_t (f) (int64_t)) { 
	push(s, f(pop(s).value)); 
}
void lift_binop(struct stack *s, int64_t (f) (int64_t, int64_t)) {
	struct maybe_i64 op1 = pop(s);
	struct maybe_i64 op2 = pop(s);
	if(op1.valid && op2.valid)
		push(s, f(op2.value,op1.value));
}
void interpret_push(struct vm_state* state) { push(& state->data_stack, state->ip->as_bc_arg64.arg); }

void interpret_iread(struct vm_state* state ) {
	struct maybe_i64 i = read_int64();
	if(i.valid)
		push(&state->data_stack, i.value);
	else {
		printf("Not a number\n");
		interpret_stop(state);
	}
}
void interpret_iprint(struct vm_state *state ) {
	struct maybe_i64 p = pop(&state->data_stack);
	if(p.valid)
		printf("%" PRId64 "\n", p.value);
	else
		interpret_stop(state);
}
int64_t i64_dub(int64_t v) { return v; }
void interpret_ipop( struct vm_state *state ) { pop(& state->data_stack); }
void interpret_stop( struct vm_state *state ) { state->ip=NULL; }
void interpret_iadd( struct vm_state* state ) { lift_binop(& state->data_stack, i64_add); }
void interpret_isub( struct vm_state* state ) { lift_binop(& state->data_stack, i64_sub); }
void interpret_imul( struct vm_state* state ) { lift_binop(& state->data_stack, i64_mul); }
void interpret_idiv( struct vm_state* state ) { 
	struct maybe_i64 op1 = pop(& state -> data_stack);
	struct maybe_i64 op2 = pop(& state -> data_stack);
	if(op1.valid && op2.valid && i64_div(op2.value, op1.value).valid)
		push(&state->data_stack, i64_div(op2.value, op1.value).value);
	else
		interpret_stop(state);
}
void interpret_icmp( struct vm_state* state ) { lift_binop(& state->data_stack, i64_cmp); }
void interpret_ineg( struct vm_state* state ) { lift_unop (& state->data_stack, i64_neg);  }
void interpret_idub( struct vm_state *state ) {
	struct maybe_i64 i = pop(& state -> data_stack);
	if(i.valid) {
		if(push(&state->data_stack,i.value))
			push(&state->data_stack,i.value);
		else
			interpret_stop(state);
	}
}
void interpret_iswp(struct vm_state *state) {
	struct maybe_i64 op1 = pop(& state -> data_stack);
	struct maybe_i64 op2 = pop(& state -> data_stack);
	if(op1.valid && op2.valid) {
		if(push(&state->data_stack,op1.value))
			push(&state->data_stack,op2.value);
		else
			interpret_stop(state);
	}
}
void (*interpreters[]) (struct vm_state *state) = {
	[BC_IREAD] = interpret_iread,
	[BC_IPRINT] = interpret_iprint,
	[BC_PUSH] = interpret_push,
	[BC_POP] = interpret_ipop,
	[BC_DUB] = interpret_idub,
	[BC_SWAP] = interpret_iswp,
	[BC_IADD] = interpret_iadd,
	[BC_ISUB] = interpret_isub,
	[BC_IMUL] = interpret_imul,
	[BC_IDIV] = interpret_idiv,
	[BC_ICMP] = interpret_icmp,
	[BC_INEG] = interpret_ineg,
	[BC_STOP] = interpret_stop
};
void interpret(struct vm_state *state) {
	for(;;) {
		interpreters[state->ip->opcode](state);
		if(!state->ip)
			return;
		state->ip++;
	}
}
void interpret_program(union ins *program) {
	struct vm_state state = vm_state_create(program);
	interpret(&state);
	print_stack(&(state.data_stack));
	vm_state_destroy(&state);
}
int main(void) {
	/* interpret_program(program); */
/* TODO: check stack overwflow while pushing to stack */
}
