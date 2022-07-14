#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
struct array {
};
int64_t square(int64_t x) { return x*x; }
double sum_of_doubles(double x, double y) { return x+y; }
/* typedef */
typedef char ftype(const float *, size_t(*)(struct array, int));
int main(void) {
	int64_t array[] = {1,2,3,4,5};
	const size_t count = sizeof(array)/sizeof(array[0]);
	int64_t (*mapper)(int64_t) = &square;
	for(size_t i=0;i<count;i++)
		array[i]=(*mapper)(array[i]);
	for(size_t i=0;i<count;i++)
		printf("%" PRId64 " ", array[i]);
	printf("\n");

	double (*sum_mapper)(double x, double y) = &sum_of_doubles;	
	for(size_t i=0;i<count;i++)
		array[i]=(*sum_mapper)(array[i],3.0);
	for(size_t i=0;i<count;i++)
		printf("%" PRId64 " ", array[i]);

	printf("\n");
	return 0;
}
