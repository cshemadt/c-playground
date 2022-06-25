#include <stdio.h>
#include <math.h>
#define MAX_LENGTH 1000
void bin(char binary[],int n) {
	long i;
	int ind=0;
	for(i=1<<8;i>0;i/=2) {
		if((n&i)==0)
			binary[ind++]='0';
		else
			binary[ind++]='1';
	}
	binary[ind]='\0';
}
// 2-6
int setbits(int x,int n);
int main() {
	int x=180;
	printf("%d\n",setbits(x, 3));
}
int setbits(int x,int n) {
	int mask=pow(2,n)-1;
	return x | mask;
}
