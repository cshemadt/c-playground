#include <stdio.h>
#define MAX_LENGTH 1000
int n=3;
void detab(int start_index,char line[]);
int fold(char line[],int len);
int get_line(char line[]);
char lines[MAX_LENGTH][MAX_LENGTH];
int main()
{
	int len;
	char line[MAX_LENGTH];
	while((len=get_line(line)) < MAX_LENGTH)
	{
		if (len>=n)
		{
			int splitted_len=fold(line,len);
			for(int i=0;i<splitted_len;i++)
				printf("%s\n",lines[i]);
		}
	
	}
}
int fold(char line[], int len)
{
	int ind=0;
	for(int i=0;i<n-1;i++)
	{
		lines[ind][i]=line[i];
	}
	ind++;
	for(int i=0;i<len-n;i++)
	{
		lines[ind][i]=line[i+n-1];
	}
	return ind+1;
}
int get_line(char line[])
{
	int c,i;
	for(i=0;i<MAX_LENGTH && ((c=getchar())!=EOF) && c!='\n';i++)
		line[i]=c;
	if(c=='\n')
	{
		line[i]=c;
		i++;
	}
	line[i]='\0';
	return i;
}
// 1-20
void detab(int start_index,char line[])
{
	for(int i=0;i<n;i++)
	{
		/*printf("%d\n",n);*/
		line[start_index+i]='_';
	}
	for(int i=0;i<n;i++)
	{
		/*printf("%d\n",n);*/
		line[start_index+i]='_';
	}
}
