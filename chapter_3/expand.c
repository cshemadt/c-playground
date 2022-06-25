#include <string.h>
#include <stdio.h>
#define MAX_LENGTH 1000
void expand(char s1[], char s2[]);
int main() {
    char s1[] = "--a--a-z";
    char s2[MAX_LENGTH]="";
    expand(s1,s2);
    printf("%s\n",s2);
}
void expand(char s1[], char s2[]) {
    int i,j;
    char from,to;
    for(i=1,j=0;i<strlen(s1)-1;i++) {
        if(s1[i] == '-' && (s1[i-1]!='-' && s1[i+1]!='-')) {
			int prev=to;
            from = s1[i-1];
			if(prev == from) {
				from++;
			}
            to = s1[i+1];
            for(;from<=to;from++,j++) {
                s2[j]=from;
            }
        }
    }
    s2[j]='\0';
}
