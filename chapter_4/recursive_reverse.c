#include <stdio.h>
#include <string.h>
int ind=0;
// void recursive_reverse(char s[], int n,int tmp,int len);
void recursive_reverse(char s[]);
int main() {
    char s[100]="hello";
    recursive_reverse(s);
    printf("%s\n",s);
}
// void recursive_reverse(char s[], int n,int tmp, int len) {
//     if(n<len/2)
//         recursive_reverse(s,n+1,s[len-n-1],len);
//     printf("%s %d %c\n",s,n,tmp);
//     s[len-n]=s[n-1];
//     s[n-1]=tmp;
// }   
void recursive_reverse(char s[]) {
    static int i,j;
    if(j==0)
        j=strlen(s)-1;
    int tmp;
    if(i<j) {
        tmp=s[i];
        s[i++]=s[j];
        s[j--]=tmp;
        recursive_reverse(s);
    }
}
