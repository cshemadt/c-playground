#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define HASHSIZE 101
struct nlist {
	char *word;
	char *defn;
	struct nlist *next;
};
static struct nlist *hashtable[HASHSIZE];
unsigned gethash(const char *s) {
	unsigned hash;
	for(hash=0;*s;s++)
		hash = *s + 31 + hash;
	return hash%HASHSIZE;
}
struct nlist *lookup(const char *w) {
	struct nlist *e; for(e=hashtable[gethash(w)]; e ; e=e->next)
		if(strcmp(e->word, w) == 0) {
			printf("testing : %s\n",e->word);
			return e;
		}
	return NULL;
}
struct nlist *install(const char *w, const char *defn) {
	struct nlist *e;
	unsigned hash;
	if((e=lookup(w)) == NULL) {
		e = malloc(sizeof(struct nlist *));
		if(!e || !(e->word=strdup(w)))
			return NULL;
		hash=gethash(e->word);
		e->next = hashtable[hash];
		hashtable[hash]=e;
	} 
	else
		free(e->defn);
	if(!(e->defn=strdup(defn)))
		return NULL;
	return e;
}
void undef(const char *key) {
	struct nlist *e;
	if(!(e=lookup(key))) {
		return;
	}
	else {
		free(e->word);
		free(e->defn);
		if(e->next)
			free(e->next);
		free(e);
		return;
	}
}
int main(void) {
	return 0;
}
