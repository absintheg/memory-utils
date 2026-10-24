cmake_minimum_required(VERSION 3.16)
project(MemoryModule LANGUAGES C)

add_library(mem STATIC
	fixed_buffer_allocator.c
	arena_allocator.c
	allocator.c
	array.c
)

target_include_directories(mem
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()
