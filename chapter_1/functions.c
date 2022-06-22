#include <stdio.h>
#define MAX_LENGTH 1000
int get_line(char line[], int length);
void copy(char from[], char to[]);
int main(int argc, char** argv)
{
	int len,max,ind;
	char line[MAX_LENGTH];
	char longest_line[MAX_LENGTH];
	char longest_lines_array[MAX_LENGTH][MAX_LENGTH];
	max=ind=0;
	while((len=get_line(line, MAX_LENGTH))>0)
	{
		if(len>10)
		{
			copy(line,longest_lines_array[ind]);
			ind++;
		}
	}
	for(int i=0;i<ind;i++)
		printf("%s\n",longest_lines_array[i]);
}
/* getline: read a line into line, return length */
int get_line(char line[], int length)
{
	int c,i;
	for(i=0;i<length && ((c=getchar())!=EOF) && c!='\n';i++)
		line[i]=c;
	if(c=='\n')
	{
		line[i]=c;
		i++;
	}
	line[i]='\0';
	return i;
}
/* copy: copy 'from' into 'to'; assume to is big enough */
void copy(char from[], char to[])
{
	for(int i=0;i<MAX_LENGTH;i++)
		to[i]=from[i];
}
