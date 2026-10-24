// Placeholder tests

#include <assert.h>
#include <stdio.h>

#include "allocator.h" // IWYU pragma: keep
#include "array.h"     // IWYU pragma: keep

void test_allocator(Allocator alloc) {
    int *buffer = allocator_alloc(alloc, sizeof(int) * 5);
    buffer[4] = 0;
    allocator_free(alloc, buffer);
}

int main() {
    printf("Tests running\n");

    int falloc_buffer[50] = {0};
    FixedBufferAllocator falloc =
        fixed_buffer_allocator_create(falloc_buffer, sizeof(falloc_buffer));
	Allocator alloc = fixed_buffer_allocator_get_allocator(&falloc);

	test_allocator(alloc);

	test_allocator(std_allocator);

    return 0;
}
