add_library(mem STATIC
	fixed_allocator.c
	allocator.c
	array.c
)

target_include_directories(mem INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)
