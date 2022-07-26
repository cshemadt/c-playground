#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
void reverse(char *s,size_t sz) {
	for(size_t i=0;i<sz/2;i++) {
		char tmp=s[i];
		s[i]=s[sz-1-i];
		s[sz-1-i]=tmp;
	}
}
double to_float(char s[]) {
    double val,power;
    int i, sign,exp_sign;
    i=0;
    sign=(s[i]=='-') ? -1 : 1;
	if(sign==-1)
		i++;
    for(val=0.0;isdigit(s[i]);i++)
        val=10.0*val+(s[i]-'0');
    if(s[i]=='.' || s[i]==',')
        i++;
    for(power=1.0;isdigit(s[i]);i++) {
        val=10*val+(s[i]-'0');
        power*=10;
    }
    if(s[i]=='e' || s[i]=='E') {
        i++;
        double exp;
        exp_sign=(s[i]=='-') ? -1 : 1;
        for(;!isdigit(s[i]);i++)
            ;
        for(exp=0;isdigit(s[i]);i++)
            exp = 10*exp+(s[i]-'0');
        switch(exp_sign) {
            case -1:
                return sign*val/(power*pow(10,exp));
                break;
            case 1:
                return sign*val/power*pow(10,exp);
                break;
        }
    }
    return sign*val/power;
}
void miniscanf(char *fmt, ...) {
	va_list args;
	va_start(args,fmt);
	char *p;
	for(p=fmt;*p;p++) {
		if(*p!='%')
			continue;
		switch(*++p) {
			case 'c': 
				{
					fread(va_arg(args,char *),1,1,stdin);
					break;
				}
			case 'd':
				{
					int *tmp = va_arg(args,int *);
					*tmp=0;
					char buf[10];
					int base=1;
					size_t sz=0; int val=0; char ch;
					while((ch=getchar())!='\n') {
						if(isalpha(ch) || ispunct(ch)) {
							*tmp=0;
							return;
						}
						else if(ch==' ' || ch=='\t')
							continue;
						buf[sz++]=ch;
					}
					for(size_t i=0;i<sz;i++) {
						*tmp += (buf[sz-i-1]-'0') * base;
						base*=10;
					}
					break;
				}
			case 'f':
				{
					char ch;
					char buf[10];
					size_t sz=0;
					while((ch=getchar())!='\n') {
						if(isalpha(ch)) {
							return;
						}
						else if(ch==' ' || ch=='\t')
							continue;
						buf[sz++]=ch;
					}
					*(double *)va_arg(args,double *)=to_float(buf);;
				}
		}
	}
}
int main(void) {
	char *ch;
	double dval=0;
	miniscanf("%f",&dval);
	/* scanf("%d",&ival); */
	printf("%f\n",dval);
	return 0;
}
