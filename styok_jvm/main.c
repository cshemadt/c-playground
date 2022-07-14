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
const union ins program[] = {
	{BC_IREAD},
	{BC_IREAD},
	{BC_DUB},
	{.as_bc_arg64 = {BC_PUSH, .arg=10}},
	{BC_IMUL},
    {BC_IADD},
    {BC_IADD},
    {BC_IPRINT},
    {BC_STOP}
};
int main(void) {
}
