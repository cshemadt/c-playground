#include <stdio.h>
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
int main(void) {
    char s1[]="char1";
    char s2[]="char2";
    strcpy_pointer_version(s1,s2);
    printf("%s %s\n",s1,s2);
}