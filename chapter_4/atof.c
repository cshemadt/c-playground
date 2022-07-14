#include <math.h>
#include <ctype.h>
#include <stdio.h>
double atof(char s[]);
int main() {
    char s[]="3.1444e+3";
    printf("%f\n",atof(s));
}
double atof(char s[]) {
    double val,power;
    int i, sign,exp_sign;
    i=0;
    sign=(s[i]=='-') ? -1 : 1;
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
