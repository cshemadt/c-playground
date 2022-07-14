#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
int int64_comparator(const int64_t *x,const int64_t *y) {
	if(*x>*y) return 1;
	if(*x>*y) return -1;
	return 0;
}
int comparator(const void *x, const void *y) {
	return int64_comparator(x,y);
}
int main(void) {
	int64_t array[] = {32432,444,33,2,1232543,7887,2212,0,-1000};
	const size_t size = sizeof(array)/sizeof(array[0]);
	qsort(array, size, sizeof(int64_t), comparator);
	for(size_t i=0;i<size;printf("%" PRId64 " ",array[i++])) ;
	return 0;
}
