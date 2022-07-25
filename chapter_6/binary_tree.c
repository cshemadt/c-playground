#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

#define MAX_WORDS_COUNT 100
#define MAX_WORD_LEN 100
#define TEST_STRINGS_COUNT 10

struct tnode {
	char *word;
	size_t count;
	struct tnode *left;
	struct tnode *right;
};
/* strdub alternative */
char *strduplicate(char *s) { 
	char *p;
	p=malloc(strlen(s)+1);
	if(p)
		strcpy(p,s);
	return p;
}
struct tnode *talloc() {
	return (struct tnode *) malloc(sizeof(struct tnode));
}
void treefree(struct tnode *r) {	
	if(r) {
		treefree(r->left);
		free(r->word);
		treefree(r->right);
		free(r);
	} 
}
void treeprint(struct tnode *root) {
	if(root) {
		treeprint(root->left);
		printf("%s %zu\n",root->word, root->count);
		treeprint(root->right);
	}
}
struct tnode *addtree(struct tnode *node, char *w) {
	int cond;
	if(node==NULL) {
		node=talloc();
		if(node) {
			node->word = strduplicate(w);
			node->count = 1;
			node->left=node->right=NULL;
		} 
	}
	else if((cond = strcmp(w,node->word)) == 0)
		node->count++;
	else if(cond < 0)
		node->left=addtree(node->left,w);
	else
		node->right=addtree(node->right,w);
	return node;
}
void destroy_array(char *words[],size_t sz) {
	for(size_t i=0;i<sz;i++)
		free(words[i]);
}
struct tnode *getwords(char *str) { 
	struct tnode *r=NULL;
	size_t i,j,k;
	char token[MAX_WORD_LEN];
	for(i=0,j=0;str[i];i++) {
		if(!isalpha(str[i]) || i==strlen(str)-1) {
			if(i==strlen(str)-1 && isalpha(str[i])) {
				token[j++]=str[i];
			}
			token[j]='\0';
			if(j>0)
				r=addtree(r, token);
			j=0;
		}
		else
			token[j++]=str[i];
	}
	return r;
}
int main(void) {
	char *str = "for void int 2 ,, ;; print. char getts ptr pointer sssdsadas3 ptr csdjvjvjvkasd! psdpsdsodsdsj char ";
	struct tnode *root = getwords(str);
	treeprint(root);
	treefree(root);
}
