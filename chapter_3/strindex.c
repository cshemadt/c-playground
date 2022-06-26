#include <stdio.h>
#define max(a,b) (a>b)?a:b
int strindex(char src[], char pattern[]);
int rightmost_strindex(char src[], char pattern[]);
int main() {
    char str1[] = "worldoworld";
    char pattern[] = "world";
    printf("%d\n",rightmost_strindex(str1,pattern));
}
int strindex(char src[], char pattern[]) {
    int i,j;
    j=0;
    for(i=0;src[i]!='\0';i++) {
        while(src[i+j]==pattern[j]) {
            /* signal that pattern is matched */
            if(pattern[j+1]=='\0')
                return i;
            j++;
        }
    }
    return -1;
}
int rightmost_strindex(char src[], char pattern[]) {
    int i,j;
    int r_index=-1;
    j=0;
    for(i=0;src[i]!='\0';i++) {
        j=0;
        while(src[i+j]==pattern[j]) {
            /* signal that pattern is matched */
            if(pattern[j+1]=='\0')
                r_index=max(r_index,i);
            j++;
        }
    }
    return r_index;
}