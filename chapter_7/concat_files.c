#include <stdio.h>
#include <stdlib.h>
/* concatenate files, version 1 */
int main(int argc, char **argv) {
	FILE *fp;
	void filecopy(FILE *, FILE *);
	if(argc==1)
		filecopy(stdin, stdout);
	else
		while(--argc > 0)
			if(!(fp=fopen(*++argv,"r"))) {
				fprintf(stderr,"cat: can't open %s.\n",*argv);
				exit(1);
			} else {
				filecopy(fp,stdout);
				fclose(fp);
			}
	if(ferror(stdout)) {
		fprintf(stderr,"%s: error writing stdout\n",argv[0]);
		exit(2);
	}
	return 0;
}
void filecopy(FILE *ifp, FILE *ofp) {
	int c;
	while((c=getc(ifp)) != EOF)
		putc(c,ofp);
}
