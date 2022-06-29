#include <stdio.h>
int mystrlen(char *s);
int strange_strlen(char *s);
int main() {
    int arr[10] = {1,2,3,4,5,6,7,8,9,10};
    char chararr[100]="char array";
    char *s="char pointer";
    int *parr;
    parr=arr;
    printf("%d\n",mystrlen("constant string"));
    printf("%d\n",mystrlen(chararr));
    printf("%d\n",mystrlen(s));
    printf("%d\n",strange_strlen(s));
}
int mystrlen(char *s) {
    int n;
    for(n=0;*s!='\0';s++,n++) ;
    return n;
}
int strange_strlen(char *s) {
    char *p;
    for(p=s;*p!='\0';p++) ;
    return p-s;
}