#ifndef FIXED_BUFFER_ALLOCATOR_H
#define FIXED_BUFFER_ALLOCATOR_H

#include <stdlib.h>
#include <string.h>

#include "allocator_interface.h"

typedef struct {
    size_t len;
} FixedBufferAllocatorBlockHeader;

typedef struct {
    void *buffer;
    size_t capacity;
    size_t used;
} FixedBufferAllocator;

extern AllocatorCallbacks fixed_buffer_allocator_callbacks;

FixedBufferAllocator fixed_buffer_allocator_create(void *buffer, size_t capacity);
Allocator fixed_buffer_allocator_get_allocator(FixedBufferAllocator *fixed_allocator);

#endif
