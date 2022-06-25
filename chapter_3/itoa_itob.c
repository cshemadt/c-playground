#include <stdio.h>
void reverse(char s[], int n) {
	for(int j=0;j<n/2;j++)
	{
		char tmp=s[j];
		s[j]=s[n-j-1];
		s[n-j-1]=tmp;
	}
}
void itoa(int n, char s[]) {
	int i,j;
	int sign;
	if((sign=n)<0)
		n=-n;
	i=0;
	do s[i++]=(n%10)+'0';
	while((n/=10)>0);
	if(sign<0)
		s[i++]='-';
	s[i]='\0';
	reverse(s, i);
} 
void itob(int n, int b, char s[]) {
	int i,j,sign;
	i=0;
	if((sign=n)<0)
		n=-n;
	do s[i++]=(n%b)+'0';
	while((n/=b)>0);
	if(sign<0)
		s[i++]='-';
	s[i]='\0';
	reverse(s,i);
}
int main() {
}
