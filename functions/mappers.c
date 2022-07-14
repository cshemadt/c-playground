#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
int64_t square(int64_t x) { return x*x; }
int64_t cube(int64_t x) { return x*x*x; }
void map(int64_t *array, size_t count, int64_t (*T)(int64_t)) {
	for(size_t i=0;i<count;i++) 
		array[i]=T(array[i]);
}
void print_arr(int64_t *arr, size_t len) { for(size_t i=0;i<len;printf("%" PRId64 " ", arr[i++])); }
int main(void) {
	int64_t array[]={1,2,3,4,5};
	size_t len=sizeof(array)/sizeof(array[0]);
	map(array, len, square);
	print_arr(array, len);
	printf("\n");
	map(array, len, cube);
	print_arr(array, len);
	printf("\n");
	return 0;
}
