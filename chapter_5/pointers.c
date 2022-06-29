#include <stdio.h>
#include <math.h>
#include <ctype.h>
#define SIZE 5
void swap(int*,int*); 
int getint(int *pn); 
double getfloat(double *pf);
int main(void) { 
    int n;
    double array[SIZE]={0.0};
    for(n=0;n<SIZE && getfloat(&array[n])!=EOF;n++)
        ;
    for(int i=0;i<SIZE;i++) {
        printf("%.2f\n",array[i]);
    }
}
void swap(int *x, int *y) {
    int tmp=*x;
    *x=*y;
    *y=tmp;
}
int getint(int *pn) {
    int c,sign;   
    while(isspace(c=getchar()))
        ;
    /* not a number */
    if(!isdigit(c) && c!=EOF && c!='+' && c!='-')
        return 0;
    sign=(c=='-')?-1:1;
    if(c=='+' || c=='-')
        c=getchar();
    for(*pn=0;isdigit(c);c=getchar())
        *pn=(*pn)*10+(c-'0');
    *pn*=sign;
    return c;
}
double getfloat(double *pf) {
    int c;
    double sign, power;
    while(isspace(c=getchar()))
        ;
    /* not a number */
    if(!isdigit(c) && c!='-' && c!='+' && c!='.')
        return 0;
    sign=(c=='-')?-1.0:1.0;
    if(c=='+' || c=='-')
        c=getchar();
    for(*pf=0.0;isdigit(c);c=getchar()) {
        *pf=(*pf)*10.0+(c-'0');
    }
    if(c=='.')
        c=getchar();
    for(power=1;isdigit(c);c=getchar(),power*=10) {
        *pf=(*pf)*10.0+(c-'0');
    }
    *pf*=sign/power;
    return c;
}