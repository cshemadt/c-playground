#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
int64_t read_int64() {
	int64_t x;
	scanf("%" PRId64, &x);
	return x;
}
size_t read_size() {
	size_t x;
	scanf("%zu",&x);
	return x;
}
void array_int_fill(int64_t* array, size_t size) {
	if(array)
		for(size_t i=0;i<size;i++)
			array[i]=read_int64();
}
int64_t* array_int_read(size_t* size) {
	int64_t* arr=malloc(sizeof(int64_t)*(*size));
	array_int_fill(arr, *size);
	return arr;
}
int64_t** marray_read(size_t* rows, size_t** sizes) {
	*rows=read_size();
	*sizes = malloc(sizeof(size_t) * (*rows));
	int64_t** marray = malloc(sizeof(int64_t*) * (*rows));
	for(size_t i=0;i<(*rows);i++) {
		(*sizes)[i]=read_size();
		(*marray)[i]=array_int_read((*sizes)[i]);
	}
	// for(size_t i=0;i<(*rows);i++) {
	// 	printf("%" PRId64 " " )
	// }
}
int main(void) {
	size_t* sizes=NULL;
	size_t rows;
	int64_t** marray = marray_read(&rows,&sizes);
	for(size_t i=0;i<rows;i++) {
		printf("%" PRId64 " ", (*marray)[i]);
	}
}