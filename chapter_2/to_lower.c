#include <stdio.h>
#define ASCII_SHIFT 32
void to_lower(char s[]);
int main() {
    char str[]="mY_stRinG";
    printf("%s\n",str);
    to_lower(str);
    printf("%s\n",str);
}
void to_lower(char s[]) {
    for(int i=0;s[i]!='\0';i++)
        s[i]=(s[i]>='A' && s[i] <= 'Z') ? s[i]+ASCII_SHIFT : s[i];
}