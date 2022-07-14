#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>

typedef int64_t i64;
typedef int32_t i32;

enum either_type {ET_INT, ET_STRING};
struct either_int_string {
	enum either_type type;
	union {
		char* as_string;
		i64 as_int;
	};
};
struct either_int_string either_from_string(char *s) {
	return (struct either_int_string) {.type = ET_STRING, .as_string = s};
}
struct either_int_string either_from_int(i64 i) {
	return (struct either_int_string) {.type = ET_INT, .as_int = i};
}
void either_int_string_destroy(struct either_int_string el) {
	if(el.type == ET_STRING)
		free(el.as_string);
}
void print(struct either_int_string e) {
	switch (e.type) {
		case ET_INT:
			printf("%" PRId64 "\n", e.as_int);
			break;
		case ET_STRING:
			printf("%s",e.as_string);
			break;
		default:
			break;
	}
}
int main(void) {
}
