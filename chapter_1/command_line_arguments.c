#include <stdio.h>
#include <string.h>
void argumentsInfo(int argc,char** argv)
{
	printf("Name of the program is: %s\n",argv[0]);
	printf("Arguments passed: %d\n",argc);
	if(argc >= 2)
	{
		for(int i=1;i<argc;i++)
		{
			printf("%d argument is: %s\n",i,argv[i]);
		}
	}

}
void argumentsInfo2(int argc, char**argv)
{
	int i=1;
	while(i<argc-1)
	{
		if(!strcmp(argv[i],"-v"))
		{
			printf("Version of this program is: 3.0.15\n");
			i++;
		}
		if(!strcmp(argv[i],"-o"))
		{
			printf("Output directory is: %s\n",argv[i+1]);
			i+=2;
		}
	}
	// and so on....
}
int main(int argc, char** argv)
{
	//argumentsInfo(argc, argv);
	argumentsInfo2(argc, argv);
}
