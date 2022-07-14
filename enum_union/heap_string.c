#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct heap_string {
    char *addr;
};
struct heap_string halloc(const char *s) {
    struct heap_string hs;
    hs.addr=(char*)malloc(strlen(s)+1);
    for(size_t i=0;i<strlen(s);i++)
        hs.addr[i]=s[i];
    return hs;
}
void heap_string_free(struct heap_string h) {
    free(h.addr);
}
int main(void) {
    struct heap_string s = halloc("hello");
    printf("%s\n", s.addr);
    heap_string_free(s);
}
