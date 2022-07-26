#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void minprintf(char *fmt, ...) {
	va_list ap; /* points to each unnamed argument in turn*/
	char *p,*sval;
	int ival;
	double dval;
	va_start(ap, fmt); /* make ap point to 1st unnamed argument */
	for(p=fmt;*p;p++) {
		if(*p!='%') {
			putchar(*p);
			continue;
		}
		switch(*++p) {
			case 'd':
				ival=va_arg(ap,int);
				printf("%d",ival);
				break;
			case 'f':
				dval=va_arg(ap,double);
				printf("%f",dval);
				break;
			case 's':
				sval=va_arg(ap,char *);
				printf("%s",sval);
				break;
			case 'x':
				ival=va_arg(ap,int);
				printf("%x", ival);
				break;
			default:
				putchar(*p);
				break;
		}
	}
	va_end(ap);
}
int main(void) {
	return 0;
}
