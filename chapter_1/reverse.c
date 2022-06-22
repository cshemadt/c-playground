#include <stdio.h>
#define LENGTH_LIMIT 1000
void reverse(char s[],int len);
int get_line(char line[],int limit);
int main(int argc, char** argv)
{
	int len;
	char line[LENGTH_LIMIT];
	while((len=get_line(line, LENGTH_LIMIT))>0)
	{
		printf("Orignal: %s\n",line);
		reverse(line,len);
		printf("Reversed: %s\n",line);
	}
}
// 1-19
void reverse(char s[], int len)
{
	for(int i=0;i<len/2;i++)
	{
		char tmp=s[i];
		s[i]=s[len-i-1];
		s[len-i-1]=tmp;
	}
}
int get_line(char line[], int limit)
{
	int c,i;
	i=0;
	for(;i<limit && ((c=getchar())!=EOF) && c!='\n';i++)
		line[i]=c;
	line[i]='\0';
	return i;
}
