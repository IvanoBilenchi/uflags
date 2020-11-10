# Test targets

if(MSVC)
    set(UF_WARNING_OPTIONS /W4)
else()
    set(UF_WARNING_OPTIONS -Wall -Wextra)
endif()

add_executable(uflags-test "test.c")
target_compile_options(uflags-test PRIVATE ${UF_WARNING_OPTIONS})
target_link_libraries(uflags-test PRIVATE uflags)

add_executable(uflags-test-no-builtins "test.c")
target_compile_options(uflags-test-no-builtins PRIVATE ${UF_WARNING_OPTIONS})
target_compile_definitions(uflags-test-no-builtins PRIVATE UFLAGS_NO_BUILTINS)
target_link_libraries(uflags-test-no-builtins PRIVATE uflags)
