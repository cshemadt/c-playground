#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include "u_alloc.h"

union mem_block *find_free_block(union mem_block **last, size_t nbytes) {
    union mem_block *current = global_base;
    while(current && !(current->h.free && current->h.size >= nbytes)) {
        *last = current;
        current = current->h.next;
    }
    return current;
}
union mem_block *find_prev_block(union mem_block *block) {
    if(!block || block == global_base)
        return NULL;
    union mem_block *current;
    for(current = global_base;current;current = current->h.next) {
        if(current->h.next == block)
            return current;
    }
    return NULL;
}

void delete_block(union mem_block *block) {
    union mem_block *pblock = find_prev_block(block);
    if(!pblock) return;
    pblock->h.next = block->h.next;
}
union mem_block *get_header(void *ptr) {
    return (union mem_block *)ptr - 1;
}
union mem_block *request_space(union mem_block *last, size_t nbytes) {
    union mem_block *block;
    block = sbrk(0);
    void *request = sbrk(nbytes + U_MEM_BLOCK);
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
void u_free(void *ptr) {
    if(!ptr) return;
    union mem_block *fblock = get_header(ptr);
    if(fblock->h.free) return;
    if(fblock == global_base || !fblock->h.next) {
        fblock->h.free = 1;
        return;
    }
    delete_block(fblock);
    union mem_block *l_block = NULL;
    union mem_block *l_free_block;
    if((l_free_block = find_free_block(&l_block, 0)) == NULL) { // If no any free blocks yet -> link freed block of memory to the end of list
        fblock->h.next = l_block->h.next;
        l_block->h.next = fblock;
    } else { // Otherwise, link it to the first free block and merge it
        l_free_block->h.size += fblock->h.size;
        if(l_free_block->h.next)
            l_free_block->h.next = fblock->h.next;
    }
    fblock->h.free = 1;
}
void *u_malloc(size_t nbytes) {
    union mem_block *block;
    if(nbytes <= 0)
        return NULL;
    if(!global_base) {
        if((block = request_space(NULL, nbytes)) == NULL)
            return NULL;
        global_base = block;
    } else {
        union mem_block *last = global_base;
        if((block = find_free_block(&last, nbytes)) == NULL) {
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
void *u_realloc(void *ptr, size_t nbytes) {
    if(!ptr)
        return u_malloc(nbytes);
    union mem_block *block = get_header(ptr);
    if(block->h.size >= nbytes)
        return ptr;
    union mem_block *new = u_malloc(nbytes);
    if(!new)
        return NULL;
    memcpy(new,ptr,block->h.size);
    u_free(ptr);
    return new;
}
void *u_calloc(size_t n, size_t sz) {
    if(n <= 0 || sz <= 0)
        return NULL;
    void *ptr = u_malloc(sz*n);
    if(!ptr)
        return NULL;
    memset(ptr, 0, sz);
    return ptr;
}
int main() {}
