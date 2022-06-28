#include <stdio.h>
int ind=0;
void recursive_itoa(int n,char s[]);
int main() {
    char s[100];
    int n=198;
    recursive_itoa(n,s);
    printf("%s\n",s);
}
void recursive_itoa(int n,char s[]) {
    if(n/10)
        recursive_itoa(n/10,s);
    s[ind++]=n%10+'0';
}
