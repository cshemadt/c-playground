#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <inttypes.h>

#define KEYTAB_LEN 10
#define MAX_KEYWORD_LEN 100
#define IN 1
#define OUT 0
struct key {
	char *word;
	size_t count;
} keytab[KEYTAB_LEN] = {
	"break",0,
	"case", 0,
	"char",0,
	"int",0,
	"bool",0,
	"const",0,
	"struct",0,
	"void",0,
	"while",0,
	"for",0
}; 
void prnt_keytab(struct key *k ,size_t n) {
	for(int i=0;i<n;printf("%s-%zu\n", k[i].word,k[i].count),i++) ;
	printf("\n");
}
void swp(struct key *x, struct key *y) {
	struct key t = *x;
	*x=*y;
	*y=t;
}
size_t binsearch(struct key *k, char *s, size_t l, size_t r) {
	if(l>r)
		return -1;
	size_t m=(l+r)/2;
	if(strcmp(k[m].word, s) == 0)
		return m;
	if(strcmp(k[m].word, s) > 0)
		return binsearch(k,s,l,m-1);
	if(strcmp(k[m].word, s) < 0)
		return binsearch(k,s,m+1,r);
}
int struct_comp(const void *x, const void *y) {
	struct key *a=(struct key *)x;
	struct key *b=(struct key *)y;
	return strcmp(a->word, b->word);
}
void sort_by_keyword(struct key *k, size_t sz) {
	qsort(k, sz, sizeof(struct key), struct_comp);
}
void find_keywords_in_string(const char *s) {
	size_t i,j;
	char str[MAX_KEYWORD_LEN];
	i=j=0;
	while(s[i]) {
		if(i==strlen(s)-1) {
			str[j]=s[i];
			str[++j]='\0';
			size_t ind=binsearch(keytab, str, 0, KEYTAB_LEN-1);
			printf("%zu\n",ind);
			if(ind!=-1)
				keytab[ind].count++;
		}
		if(s[i] == '\n' || s[i] == ' ' || s[i] == '\t') {
			str[j]='\0';
			size_t ind=binsearch(keytab, str, 0, KEYTAB_LEN-1);
			printf("%zu\n",ind);
			if(ind!=-1)
				keytab[ind].count++;
			j=0;
		}
		else if(isalpha(s[i])) {
			str[j]=s[i];
			j++;
		}
		i++;
	}
}
int main(void) {
}
