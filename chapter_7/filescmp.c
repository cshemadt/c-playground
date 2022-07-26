#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE 100
int main(int argc, char **argv) {
	FILE *fp1;
	FILE *fp2;
	while(--argc > 0) {
		fp2=fopen(argv[argc],"r");
		if(!fp2) {
			fprintf(stderr, "can't open file %s\n",argv[argc]);
			return 1;
		} else {
			fp1=fopen(argv[--argc],"r");
			if(!fp1) {
				fprintf(stderr, "can't open file %s\n",argv[argc]);
				return 1;
			}}
	}
	char str1[MAXLINE];
	char str2[MAXLINE];
	char resultstr[MAXLINE];
	while(fgets(str1,MAXLINE,fp1) && fgets(str2,MAXLINE, fp2)) {
		if(strcmp(str1,str2)!=0) {
			fputs(str1,stdout);
			fputs(str2,stdout);
			break;
		}
	}
	return 0;
}
