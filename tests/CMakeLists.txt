add_executable(mem_tests tests.c)

target_link_libraries(mem_tests
    PRIVATE mem
)

add_test(
    NAME mem_tests
    COMMAND mem_tests
)
