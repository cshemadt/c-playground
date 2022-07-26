#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAXLINES 100
size_t find(char *pattern, FILE *fp) {
	size_t found=0;
	char line[MAXLINES];
	while(fgets(line, MAXLINES, fp)) {
		if(strstr(line,pattern)) {
			++found;
		}
	}
	return found;
}
int main(int argc, char **argv) {
	FILE *fp;
	size_t found;
	char *pattern = argv[--argc];
	if(argc == 1) {
		fp=stdin;
		if((found=find(pattern,fp)) > 0)
			printf("%zu entries of pattern\n",found);
		else
			printf("Pattern not found\n");
		fclose(fp);
	}
	else {
		while(--argc > 0) {
			fp=fopen(argv[argc],"r");
			if(!fp) {
				printf("%s: can't open file %s\n",argv[0],argv[argc]);
				exit(1);
			}
			printf("File %s:\n",argv[argc]);
			if((found=find(pattern,fp)) > 0)
				printf("%zu entries of pattern\n",found);
			else
				printf("Pattern not found\n");
			fclose(fp);
		}
	}
}
