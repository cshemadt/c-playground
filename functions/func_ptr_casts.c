#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
char f(char ch) {
	printf("F called!\n");
	return 'a'+ch; 
}
char (*p1)(char) = f;
int main(void) {
	/* from char -> char
	 * to const int64_t * -> void  */
	void (*p2)(const int64_t *) = (void(*)(const int64_t *))(p1);
	int64_t x=2;
	p2(&x);
	/* cast back to char -> char */
	char (*p3)(char) = (char(*)(char))(p2);
	printf("%c\n", p3(3));
	return 0;
}
