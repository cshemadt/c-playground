#include <stdio.h>
#include <string.h>
#define LOWER 0
#define UPPER 220
#define STEP 20
void fahr_to_celsius()
{
	for(int i=0;i<42;i++)
	{
		printf("-");
	}
	printf("\n");
	printf("|     Fahrenheit    |        Celsius     |\n");
	for(int i=0;i<42;i++)
	{
		printf("-");
	}
	float celsius=LOWER;
	printf("\n");
	for(float fahr = LOWER;fahr<UPPER;fahr+=STEP) 
	{
		celsius = 5.0*(fahr-32.0)/9.0;
		printf("| Fahr: %11.0f | Celsius: %9.2f |\n",fahr,celsius);
	}
	for(int i=0;i<42;i++)
	{
		printf("-");
	}
	printf("\n");
}
void celsius_to_fahr()
{
	for(int i=0;i<38;i++)
	{
		printf("-");
	}
	printf("\n");
	printf("|     Celsius    |    Fahrenheit     |\n");
	float fahr;
	for(int i=0;i<38;i++)
	{
		printf("-");
	}
	printf("\n");
	for(float celsius=LOWER;celsius<UPPER;celsius+=STEP)
	{
		fahr=9.0*(celsius)/5.0+32;
		printf("| Celsius: %5.0f | Fahr: %11.2f |\n",celsius,fahr);
	}
	for(int i=0;i<38;i++)
	{
		printf("-");
	}
	printf("\n");
}
void parseArguments(int argc, char** argv)
{
	int i=1;
	while(i<argc)
	{
		if(!strcmp(argv[i],"-h"))
		{
			printf("AVAILABLE OPTIONS:\n");
			printf("\"-h\"\tHelp page(you are currently here).\n");
			printf("\"-m\"\tMode, available arguments: \n\t\"f2c\"(convert table from Fahrenheit to Celsius);\n \t\"c2f\"(convert table from Celsius to Fahrenheit).\n");
			i++;
		}
		else if(!strcmp(argv[i],"-m"))
		{
			if(!strcmp(argv[i+1],"f2c"))
			{
				fahr_to_celsius();
			}
			else if(!strcmp(argv[i+1],"c2f"))
			{
				celsius_to_fahr();
			}
			i+=2;
			continue;
		}
		else
		{
			printf("AVAILABLE OPTIONS:\n");
			printf("\"-h\"\tHelp page(you are currently here).\n");
			printf("\"-m\"\tMode, available arguments: \n\t\"f2c\"(convert table from Fahrenheit to Celsius);\n \t\"c2f\"(convert table from Celsius to Fahrenheit).\n");
			i++;
			break;
		}
	}
}
int main(int argc,char** argv)
{
	parseArguments(argc, argv);
}
