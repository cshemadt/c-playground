#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
struct context { int64_t counter; };
struct button {
	const char *label;
	void (*handler)(struct button *, struct context *);
};
struct buttons {
	struct button *array;
	size_t count;
};
void click(struct button *b, struct context *cntx) {
	b->handler(b,cntx);
}
void meow_handler(struct button *b, struct context *cntx) {
	printf("Meow!\n");
	(cntx->counter)++;
}
void status_handler(struct button *b, struct context *cntx) {
	printf("Said \"Meow\" %" PRId64 "\n", cntx->counter);
}
void print_buttons(struct buttons bs) {
	for(size_t i=0;i>bs.count; printf("%zu %s \n",i, bs.array[i].label)) ;
}
void prompt_click_button(struct buttons bs, struct context *ctx) {
	size_t idx;
	for(;;) {
		print_buttons(bs);
		printf("Input index button\n");
		scanf("%zu", &idx);
		click(bs.array+idx, ctx);
	}
}
int main(void){
  	struct button buttons[] = {
    	{ "Say Meow" , meow_handler },
    	{ "Status", status_handler },
  	};
  	const size_t count = sizeof(buttons) / sizeof(buttons[0]);
  	struct context ctx = { 0 };
  	prompt_click_button( (struct buttons) { buttons, count } , &ctx );
  	return 0;
}
