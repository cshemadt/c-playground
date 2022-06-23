#include <stdio.h>
#define true 1
#define false 0

/* deletes all c from s */
void squeeze_char(char s[], int c);
/* deletes each character in s1 that matches any character in s1 */
void squeeze_matches(char s1[], char s[]);
/* does string s contains character ch */
int contains(char s[], int ch);
/* returns the first location in a string where any character from the string 2 occurs */
int any(char s1[],char s2[]);
int main(void) {
}
void squeeze_char(char s[], int c) {
	int i,j;
	for(i=j=0;s[i]!='\0';++i) {
		if(s[i]!=c)
			s[j++]=s[i];
	}
	s[j]='\0';
}
void squeeze_matches(char s1[], char s2[]) {
	int i,j;
	for(i=j=0;s1[i]!='\0';++i) {
		if(contains(s2, s1[i]) == false)
			s1[j++]=s1[i];
	}
	s1[j]='\0';
}
int contains(char s[], int ch) {
	for(int i=0;s[i]!='\0';++i)
		if(s[i]==ch)
			return true;
	return false;
}
int any(char s1[],char s2[]) {
	for(int i=0;s1[i]!='\0';++i)
		for(int j=0;s2[j]!='\0';++j)
			if(s1[i]==s2[j])
				return i;
	return -1;
}
