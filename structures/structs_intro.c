#include <stdio.h>
#include <inttypes.h>
struct point {
	int x;
	int y;
};
int main(void) {
	struct point poin1,point2;
	struct {int x; int y; } point3, point4;
	point3.x=10;
	printf("%d\n",point3.x);
}
