#include <stdio.h>
#define ASCII_LOWER_CHAR 33
#define ASCII_TOTAL_LENGTH 127
int max(int x,int y)
{
	return (x>y) ? x : y;
}
// 1-13
void words_length_histogram()
{
	int c,out;
	out=1;
	int word_lengths[20];
	int ind,curr_len,max_len;
	ind=curr_len=max_len=0;
	for(int i=0;i<20;i++)
		word_lengths[i]=0;
	
	while((c=getchar())!=EOF)
	{
		if(c!=' ' && c!='\n')
		{
			curr_len++;
			out=0;
		}
		else if(out==0)
		{
			word_lengths[ind]=curr_len;
			max_len=max(max_len,curr_len);
			out=1;
			ind++;
			curr_len=0;
		}
	}
	if(curr_len>0)
	{
		max_len=max(max_len,curr_len);
		word_lengths[ind]=curr_len;
		ind++;
	}
	printf("\nThe horizontal histogram of entered words: \n");
	for(int i=0;i<ind;++i)
	{
		for(int j=0;j<word_lengths[i];++j)
		{
			printf("-");
		}
		printf("\n");
	}
	printf("The vertical histogram of entered words: \n");
	for(int i=max_len;i>0;i--)
	{
		for(int j=0;j<ind;j++)
		{
			if(word_lengths[j]>=i)
				printf("|");
			else
				printf(" ");
		}
		printf("\n");
	}
}
// 1-14
void char_frequency_in_word()
{
	int c,mx;
	mx=0;
	int char_frequency_array[ASCII_TOTAL_LENGTH];
	for(int i=ASCII_LOWER_CHAR;i<ASCII_TOTAL_LENGTH;i++)
		char_frequency_array[i]=0;
	while((c=getchar())!=EOF)
	{
		char_frequency_array[(int)c]+=1;
		mx=max(mx,char_frequency_array[(int)c]);
	}
	// drawing histogram
	printf("\n");
	for(int i=mx;i>0;i--)
	{
		for(int j=ASCII_LOWER_CHAR;j<ASCII_TOTAL_LENGTH;j++)
		{
			if(char_frequency_array[j]>=i)
				printf("# ");
			else if(0<char_frequency_array[j] && char_frequency_array[j]<i)
				printf("  ");
		}
		printf("\n");
	}
	for(int i=ASCII_LOWER_CHAR;i<ASCII_TOTAL_LENGTH;i++)
	{
		if(char_frequency_array[i]>0)
			printf("%c ",i);
	}
	printf("\n");
}
int main(int argc,char** argv)
{
	//words_length_histogram();
	char_frequency_in_word();
}

