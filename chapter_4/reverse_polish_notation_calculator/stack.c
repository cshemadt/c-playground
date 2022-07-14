#include "calc.h"
#include <stdio.h>
#define MAX_STACK_SIZE 100
int curr_stack_position=0;
double stack[MAX_STACK_SIZE];
double pop() {
    if(curr_stack_position>0)
        return stack[--curr_stack_position];
    else {
        printf("Stack is empty\n");
        return 0;    
    }
}
void push(double val) {
    if(curr_stack_position+1>MAX_STACK_SIZE) {
        printf("Max stack length exceeded\n");
        return;
    }
    stack[curr_stack_position++]=val;
}
