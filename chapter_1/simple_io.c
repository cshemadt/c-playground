#include <stdio.h>
int num_char()
{
	long nc=0;
	while(getchar() != EOF)
		++nc;
	return nc;
}
int num_lines()
{
	long nl=0;
	int c;
	while((c=getchar()) != EOF)
	{
		if(c=='\n')
			++nl;
	}
	return nl;
}
// 1-9
void replace_blanks()
{
	int c;
	int bc=0;
	while((c=getchar())!=EOF)
	{
		if(c=='_' && bc==0)
		{
			putchar(c);
			bc++;
		}
		if(c!='_')
		{
			putchar(c);
			bc=0;
		}
	}
}
// 1-10
void replace_escape_sequences()
{
	int c;
	while((c=getchar())!=EOF)
	{
		if(c=='\t' || c=='\b' || c=='\\')
			putchar('\\');
		else
			putchar(c);
	}
}
void word_counter()
{
	int c,n;
	n=0;
	while((c=getchar())!=EOF)
	{
		if(c==' ' || c=='\n' || c=='\t')
		{
			n++;
		}
	}
	printf("%d\n",n);
}
// 1-12
void write_words_per_line()
{
	int c;
	while((c=getchar())!=EOF)
	{
		if(c==' ' || c=='\t')
		{
			putchar('\n');
		}
		else
			putchar(c);
	}
}
int main(int argc,char** argv)
{
	//printf("%d\n",num_char());
	//printf("%d\n",num_lines());
	//replace_blanks();
	//replace_escape_sequences();
	//word_counter();
	write_words_per_line();
}
