#include <math.h>
#include <stdio.h>
#include <ctype.h>
#define ASCII_SHIFT 55
int htoi(char s[]);
int my_strlen(char s[]);
int main(int argc, char** argv) {
	if(argc > 1)
	{
		printf("%d\n",htoi(argv[1]));
	}
}
int htoi(char s[]) {

	int res=0;
	int end=-1;
	int pow_base_index=0;
	if(s[0]=='0' && (s[1]=='x' || s[1]=='X'))
		end=1;
	for(int i=my_strlen(s)-1;i>end;i--) {
		if(s[i] <= '9' && s[i] >= '0') {
			res+=(s[i]-'0')*pow(16,pow_base_index);
			pow_base_index++;
		}
		else if(s[i]<='F' && s[i]>='A') {
			res+=(s[i]-ASCII_SHIFT)*pow(16,pow_base_index);
			pow_base_index++;
		}
		else {
			printf("Wrong character - %c",s[i]);
			return -1;
		}
	}
	return res;
}
int my_strlen(char s[]) {
	int i=0;
	while(s[i]!='\0')
		i++;
	return i;
}
