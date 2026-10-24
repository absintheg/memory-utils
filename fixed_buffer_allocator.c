#include <stdio.h>
#include <string.h>

#include "internal/fixed_buffer_allocator.h"

static void *fixed_buffer_allocator_alloc(void *self, size_t len) {
    FixedBufferAllocator *fixed_allocator = (FixedBufferAllocator *)self;

    size_t aligned = mem_align_forward(fixed_allocator->used, MEM_ALIGNMENT);
    size_t total = sizeof(FixedBufferAllocatorBlockHeader) + len;
    size_t end = aligned + total;

    if (end > fixed_allocator->capacity)
        return NULL;

    FixedBufferAllocatorBlockHeader *header =
        (FixedBufferAllocatorBlockHeader *)(fixed_allocator->buffer + aligned);

    header->len = len;

    void *ptr = (void *)(header + 1);
    fixed_allocator->used = aligned + total;
    return ptr;
}

static bool is_last_allocation(FixedBufferAllocator *fixed_allocator, void *ptr) {
    FixedBufferAllocatorBlockHeader *block_header = ((FixedBufferAllocatorBlockHeader *)ptr) - 1;

    size_t expected_end = (size_t)fixed_allocator->buffer + fixed_allocator->used;
    size_t buffer_end = (size_t)ptr + block_header->len;
    return buffer_end == expected_end;
}

static void *fixed_buffer_allocator_resize(void *self, size_t len, void *ptr) {
    FixedBufferAllocator *fixed_allocator = (FixedBufferAllocator *)self;

    if (is_last_allocation(fixed_allocator, ptr)) {
        FixedBufferAllocatorBlockHeader *block_header =
            ((FixedBufferAllocatorBlockHeader *)ptr) - 1;

        if (block_header->len > len) {
            fixed_allocator->used -= block_header->len - len;
        } else {
            fixed_allocator->used += len - block_header->len;
        }
        block_header->len = len;
        return ptr;
    }

    return fixed_buffer_allocator_alloc(self, len);
}

static void fixed_buffer_allocator_free(void *self, void *ptr) {
    FixedBufferAllocator *fixed_allocator = (FixedBufferAllocator *)self;
    if (!is_last_allocation(fixed_allocator, ptr)) {
        return;
    }
    FixedBufferAllocatorBlockHeader *block_header = ((FixedBufferAllocatorBlockHeader *)ptr) - 1;
    fixed_allocator->used -= block_header->len + sizeof(FixedBufferAllocatorBlockHeader);
}

AllocatorCallbacks fixed_buffer_allocator_callbacks = {
    .alloc = fixed_buffer_allocator_alloc,
    .resize = fixed_buffer_allocator_resize,
    .free = fixed_buffer_allocator_free,
};

FixedBufferAllocator fixed_buffer_allocator_create(void *buffer, size_t capacity) {
	FixedBufferAllocator out;
    out.capacity = capacity;
    out.buffer = buffer;
    out.used = 0;
	return out;
}

Allocator fixed_buffer_allocator_get_allocator(FixedBufferAllocator *fixed_allocator) {
    Allocator allocator = {
        .callbacks = &fixed_buffer_allocator_callbacks,
        .self = fixed_allocator,
    };
    return allocator;
}
