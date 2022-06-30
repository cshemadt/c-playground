#include <stdio.h>
#define MAX_SIZE 15
int mystrlen(char *s) {
    int i;
    for(i=0;s[i];i++) ;
    return i;
}
void strcpy_array_subscript(char *s, char *t) {
    int i=0;
    while( (s[i]=t[i]) != '\0') 
        i++;
}
void strcpy_pointer_version(char *s, char *t) {
    while((*s=*t)!='\0') {
        s++;
        t++;
    }
}
void complete_strcpy(char *s, char *d) {
    while(*s++=*d++) ;
}
int strcmp(char *s, char *d) {
    int i;
    for(i=0;s[i]==d[i];i++) {
        if(s[i]=='\0')
            return 0;
    }
    return s[i]-d[i];
}
int strcmp_pointer(char *s, char *d) {
    for(;*s==*d;s++,d++)
        if(*s=='\0')
            return 0;
    return *s-*d;
        
}
char *strlen_ptr(char *s) {
    for(;*s;s++) ;
    return s;
}
void mystrcat(char *s, char *t) {
    char *end_of_str;
    for(end_of_str=strlen_ptr(s);*t;end_of_str++,t++) {
        *end_of_str=*t;
    }
}
int strend(char *s, char *t) {
    int t_len=mystrlen(t);
    char *s_start = strlen_ptr(s)-t_len;
    for(;*t;s_start++,t++) {
        if(*t!=*s_start) 
            return 0;
    return 1;
    }
}
void mystrncpy(char *s, char *t,int n) {
    if(n>mystrlen(t)) {
        printf("Number n is greater than source string length\n");
        return;
    }
    else if(mystrlen(t)>mystrlen(s))
        n=mystrlen(s);
    for(int i=0;i<n;i++)
        *(s+i) = *(t+i);
}
int main(void) {
    char s[MAX_SIZE]="string";
    char t[]="chararraybiig";
    mystrncpy(s,t,3);
    printf("%s\n",s);
}