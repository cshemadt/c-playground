#include <stdio.h>
#include <inttypes.h>

typedef int64_t i64;
typedef int32_t i32;

union qword {
	i64 integer;
	i32 parts[2];
};
union vec3d {
	struct {
		double x; // == coord[0]
		double y; // == coord[1]
		double z; // == coord[2]
	};
	double coord[3];
};
int main(int argc, char **argv) {

	return 0;
}
