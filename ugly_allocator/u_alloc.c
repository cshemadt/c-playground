#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
typedef long Align;
union mem_block {
    struct header{
        size_t size;
        union mem_block *next;
        int free;
    } h;
    Align align;
}; 
#define META_SIZE sizeof(union mem_block)
#define MIN_MERGE_BLOCK_SIZE 4 // for debug  TODO: make 3 again
#define MIN_MERG_BLOCK_N 2
#define MATCH_FOR_MERGING(b) (b)->h.free && (b)->h.size < MIN_MERGE_BLOCK_SIZE
void *global_base = NULL; /* linked list head */

union mem_block *find_free_blocks(union mem_block **last, size_t nbytes) {
    union mem_block *current = global_base;
    while(current && !(current->h.free && current->h.size >= nbytes)) {
        *last = current;
        current = current->h.next;
    }
    return current;
}
void print_list(union mem_block *head) {
    while(head) {
        printf("Element of linked list. Is free: %d; size: %zu\n",head->h.free, head->h.size);
        head = head->h.next;
    }
    printf("--------------------------------\n"); // TODO: just for debugging purposes; delete it
}
union mem_block *get_header(void *ptr) {
    return (union mem_block *)ptr - 1;
}
union mem_block *request_space(union mem_block *last, size_t nbytes) {
    union mem_block *block;
    block = sbrk(0);
    void *request = sbrk(nbytes + META_SIZE);
    assert((void *)block == request);
    if(request == (void *)-1)
        return NULL;
    if(last)
        last->h.next = block;
    block->h.size=nbytes;
    block->h.next=NULL;
    block->h.free=0;
    return block;
}
//TODO: add condition when merge free blocks
void merge_small_blocks() {
    union mem_block *current = (union mem_block *)global_base;
    union mem_block *merging = NULL;
    int flag = 0;
    unsigned nmerged=0;
    unsigned merged_size = 0;
    while(current) {
        // merge entry point
        if(flag == 0 && MATCH_FOR_MERGING(current)) {
            merging = current;
            flag = 1;
            nmerged = 1;
        } else if(flag == 1 && MATCH_FOR_MERGING(current)) { // found block for merging
            nmerged++;
            merged_size += current->h.size;
        }
        if(MATCH_FOR_MERGING(current) == 0|| !current->h.next) { // if block doesn't match for merging or this is the last block in list -> reset "flags" and "nmerged"
            if(nmerged > MIN_MERG_BLOCK_N) {
                merging->h.size += merged_size;
                merging->h.next = current;
            }
            flag = nmerged = merged_size = 0;
        }
        current = current->h.next;
    }
}
void free(void *ptr) {
    union mem_block *header = get_header(ptr);
    if(!ptr || header->h.free)
        return;
    header->h.free = 1;
    merge_small_blocks();
}
void *m_malloc(size_t nbytes) {
    union mem_block *block;
    if(nbytes <= 0)
        return NULL;
    if(!global_base) {
        if((block = request_space(NULL, nbytes)) == NULL)
            return NULL;
        global_base = block;
    } else {
        union mem_block *last = global_base;
        if((block = find_free_blocks(&last, nbytes)) == NULL) {
            block = request_space(last, nbytes);
            if(!block)
                return NULL;
        }
        else {
            if(block->h.size > nbytes) {
                union mem_block *splitted = request_space(block, block->h.size-nbytes);
                splitted->h.free = 1;
                block->h.size -= (block->h.size - nbytes);
            }
            block->h.free = 0;
        }
    }
    return (block+1);
}
void *realloc(void *ptr, size_t nbytes) {
    if(!ptr)
        return m_malloc(nbytes);
    union mem_block *block = get_header(ptr);
    if(block->h.size >= nbytes)
        return ptr;
    union mem_block *new = m_malloc(nbytes);
    if(!new)
        return NULL;
    memcpy(new,ptr,block->h.size);
    free(ptr);
    return new;
}
void *calloc(size_t n, size_t sz) {
    if(n <= 0 || sz <= 0)
        return NULL;
    void *ptr = m_malloc(sz*n);
    if(!ptr)
        return NULL;
    memset(ptr, 0, sz);
    return ptr;
}
int main(void) {
    char *s = m_malloc(1);
    char *s1 = m_malloc(2);
    char *s2 = m_malloc(5);
    char *s3 = m_malloc(1);
    char *s4 = m_malloc(2);
    char *s5 = m_malloc(3);
    char *s6 = m_malloc(1);
    free(s);
    free(s1);
    free(s2);
    free(s3);
    free(s4);
    free(s5);
    free(s6);
    print_list(global_base);
}
