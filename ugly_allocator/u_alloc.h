typedef long Align;
union mem_block {
    struct header{
        size_t size;
        union mem_block *next;
        int free;
    } h;
    Align align;
}; 
#define U_MEM_BLOCK sizeof(union mem_block)
void *global_base = NULL; /* linked list head */


union mem_block *find_free_block(union mem_block **last, size_t nbytes);
union mem_block *find_prev_block(union mem_block *block);
union mem_block *get_header(void *ptr);
union mem_block *request_space(union mem_block *last, size_t nbytes);

void delete_block(union mem_block *block);

void u_free(void *ptr);
void *u_malloc(size_t nbytes);
void *u_realloc(void *ptr, size_t nbytes);
void *u_calloc(size_t n, size_t sz);
