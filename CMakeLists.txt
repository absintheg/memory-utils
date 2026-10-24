cmake_minimum_required(VERSION 3.16)

add_library(mem STATIC
	fixed_buffer_allocator.c
	arena_allocator.c
	allocator.c
	array.c
)

target_include_directories(mem INTERFACE
	${CMAKE_CURRENT_SOURCE_DIR}
)
