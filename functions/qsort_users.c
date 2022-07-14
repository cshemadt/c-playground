#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
typedef struct { char* addr; } string_heap ;

typedef uint64_t uid;
#define PRI_uid PRIu64
#define SCN_uid SCNu64

enum city {C_SARATOV, C_MOSCOW, C_PARIS, C_LOS_ANGELES, C_OTHER};

const char* city_string[] = {
  [C_SARATOV] = "Saratov",
  [C_MOSCOW] = "Moscow",
  [C_PARIS] = "Paris",
  [C_LOS_ANGELES] = "Los Angeles",
  [C_OTHER] = "Other"
};

struct user {
   	const uid id;
   	const string_heap name;
   	enum city city;
};

/* Comparators */
int comp_user_name(const void *x, const void *y) {
	struct user *a=((struct user *)x);
	struct user *b=((struct user *)y);
	return strcmp(a->name.addr,b->name.addr);
}
int comp_city_name(const void *x, const void *y) {
	struct user *a=((struct user *)x);
	struct user *b=((struct user *)y);
	return strcmp(city_string[a->city],city_string[b->city]);
}
int comp_uid(const void *x, const void *y) {
	struct user *a=((struct user *)x);
	struct user *b=((struct user *)y);
	if(a->id > b->id)
		return 1;
	if(a->id < b-> id)
		return -1;
	return 0;
}
void users_sort_uid(struct user users[], size_t sz) {
	qsort(users, sz, sizeof(struct user), comp_uid);
}

void users_sort_name(struct user users[], size_t sz) {
	qsort(users, sz, sizeof(struct user), comp_user_name);
}

void users_sort_city(struct user users[], size_t sz) {
	qsort(users, sz, sizeof(struct user), comp_city_name);
}
int main(void) {

	struct user u1 = {.name = "Andrej", .id = 1, .city=C_MOSCOW};
	struct user u2 = {.name = "John", .id = 45, .city=C_SARATOV};
	struct user u3 = {.name = "Noll", .id = 0, .city=C_LOS_ANGELES};
	struct user users[] = {u1,u2,u3};
	size_t sz=sizeof(users)/sizeof(users[0]);
	users_sort_uid(users, sz);
	for(size_t i=0;i<sz;printf("%" PRIu64 " ", users[i++].id)) ;
	users_sort_name(users, sz);
	for(size_t i=0;i<sz;printf("%s ", users[i++].name.addr)) ;
}
