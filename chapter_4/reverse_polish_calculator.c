#include <stdio.h>
#include <ctype.h>

#define MAX_STACK_SIZE 100

double pop();
void push(double val);

double stack[MAX_STACK_SIZE];
int curr_stack_position=0;

int main() {
    char expr[]="";
    int i;
    double prev;
    for(i=0;expr[i]!='\0';i++) {
        if(isdigit(expr[i])) {
            push(expr[i]-'0');
            continue;
        }
        switch(expr[i]) {
            case '+':
                push(pop()+pop());
                break;
            case '-':
                prev=pop();
                push(pop()-prev);
                break;
            case '*':
                push(pop()*pop());
                break;
            case '/':
                prev=pop();
                push(pop()/prev);
                break;
        }
    }
    printf("%.2f\n",pop());
}

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