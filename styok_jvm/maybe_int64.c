#include <inttypes.h>
#include <stdbool.h>
struct maybe_i64 {
	int64_t value;
	bool valid;
};
struct maybe_i64 some_i64(int64_t v);
static const struct maybe_i64 none_i64 = {0};
