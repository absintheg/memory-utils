#ifndef ALLOCATOR_API_H
#define ALLOCATOR_API_H

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

static const int MEM_ALIGNMENT = 8;

typedef struct {
	void *(*alloc)(void *self, size_t len);
	void *(*resize)(void *self, size_t len, void *memory);
	void (*free)(void *self, void *memory);
} AllocatorCallbacks;

typedef struct {
	AllocatorCallbacks *callbacks;
	void *self;
} Allocator;

void *allocator_alloc(Allocator allocator, size_t len);
void *allocator_alloc_unchecked(Allocator allocator, size_t len);

void *allocator_resize(Allocator allocator, size_t len, void *ptr);
void *allocator_resize_unchecked(Allocator allocator, size_t len, void *ptr);

void allocator_free(Allocator allocator, void *ptr);

extern AllocatorCallbacks std_allocator_callbacks;
extern Allocator std_allocator;

size_t mem_align_backward(size_t ptr, size_t alignment);
size_t mem_align_forward(size_t ptr, size_t alignment);

#endif
