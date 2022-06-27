#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100
#define MAX_BUFF_SIZE 100
#define NUMBER '0'
#define MAX_OP_SIZE 100
double pop();
void push(double val);
int getop(char s[]);
int getch();
void ungetch(int c);
double stack[MAX_STACK_SIZE];
int curr_stack_position=0;
int buffer[MAX_BUFF_SIZE];
int curr_buffer_position=0;

int main() {
    int type;
    double op2;
    char s[MAX_OP_SIZE];
    while((type=getop(s))!=EOF) {
        switch(type) {
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop()+pop(0));
                break;
            case '-':
                op2=pop();
                push(pop()-op2);
                break;
            case '*':
                push(pop()*pop(0));
                break;
            case '/':
                op2=pop();
                push(op2/pop());
                break;
        }
    }
    printf("%f\n",pop());
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
/* pop char from buffer */
int getch() {
    return (curr_buffer_position>0)?buffer[--curr_buffer_position]:getchar();
}
/* push char into buffer */
void ungetch(int c) {
    if(curr_buffer_position>=MAX_BUFF_SIZE)
        printf("Too many characters\n");
    else
        buffer[curr_buffer_position++]=c;
}
int getop(char s[]) {
    int i,c;
    while((s[0]=c=getch()) == ' ' || c=='\t')
        ;
    s[1]='\0';
    if(!isdigit(c) && c!='.')
        return c;
    i=0;
    if(isdigit(c))
        while(isdigit(s[++i] = c = getch()))
            ;
    if(c=='.')
        while(isdigit(s[++i] = c = getch()))
            ;
    s[i]='\0';
    if(c!=EOF)
        ungetch(c);
    return NUMBER;
}