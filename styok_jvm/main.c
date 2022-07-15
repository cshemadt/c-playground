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
struct vm_state vm_state_create(union ins *ip) {
	return (struct vm_state) { .ip = ip, .data_stack = stack_create(STACK_CAPACITY) };
}
void vm_state_destroy(struct vm_state *vm) {
	/* maybe overhead */
	vm->data_stack.curr_stack_pos=0;
	vm->ip=NULL;

	free(vm->data_stack.data.data);
}
union ins program[] = {
	{BC_IREAD},
	{BC_IADD},
    {BC_STOP}
};
/* Move it to header file */
void interpret_push(struct vm_state* state);
void interpret_iread(struct vm_state* state );
void interpret_iprint(struct vm_state *state );
void interpret_stop(struct vm_state *state );

void interpret_ipop(struct vm_state *state);
void interpret_idup(struct vm_state *state);
void interpret_icmp(struct vm_state *state);

void interpret_iadd(struct vm_state *state );
void interpret_imul(struct vm_state *state);
void interpret_idiv(struct vm_state *state);
void interpret_isub(struct vm_state *state);

int64_t read_int64() {
	int64_t x;
	return (scanf("%" SCNd64, &x)==1) ? x : -1;
}
void interpret_push(struct vm_state* state) {
	push(& state->data_stack, state->ip->as_bc_arg64.arg);
}

void interpret_iread(struct vm_state* state ) {
	int64_t val = read_int64();
	if(val != -1)
		push(&state->data_stack, val);
	else {
		printf("Not a number\n");
		interpret_stop(state);
	}
}
void interpret_iadd(struct vm_state *state ) {
	push(&state->data_stack,pop(&state->data_stack)+pop(&state->data_stack));
}
void interpret_iprint(struct vm_state *state ) {
	int64_t p = pop(&state->data_stack);
	if(p==-1) {
		interpret_stop(state);
		return;
	}
	printf("%" PRId64 "\n", p);
}

void interpret_stop(struct vm_state *state ) {
	state->ip=NULL;
}
void (*interpreters[]) (struct vm_state *state) = {
	[BC_IREAD] = interpret_iread,
	[BC_IPRINT] = interpret_iprint,
	[BC_PUSH] = interpret_push,
	[BC_IADD] = interpret_iadd,
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
	/* print_stack(&(state.data_stack)); */
	vm_state_destroy(&state);
}
int main(void) {
	interpret_program(program);
}
