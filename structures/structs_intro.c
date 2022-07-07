#include <stdio.h>
#include <inttypes.h>
struct point {
	const char* name;
	int64_t x;
	int64_t y;
};
struct point p1 = {"11",3,9};
struct point* p1_ptr=&p1;
int main(void) {
	p1.x=30;
	p1.y=90;
    p1_ptr->x = 10;
	(*(p1_ptr)).y = 12;
	return 0;
}
