/**
 * Tests for the uFlags library.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 Ivano Bilenchi <https://ivanobilenchi.com>
 * @copyright SPDX-License-Identifier: MIT
 *
 * @file
 */

#include "uflags.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Utility macros

#define array_size(array) (sizeof(array) / sizeof(*(array)))

#define uflags_assert(exp) do {                                                                     \
    if (!(exp)) {                                                                                   \
        printf("Test failed: %s, line %d (%s)\n", __func__, __LINE__, #exp);                        \
        return false;                                                                               \
    }                                                                                               \
} while(0)

// Tests

#define uflags_test_impl(N) {                                                                       \
    UFlags(N) flags = uflags_none(N);                                                               \
    uflags_assert(flags == 0);                                                                      \
    uflags_assert(uflags_count_set(N, flags) == 0);                                                 \
    uflags_assert(uflags_count_unset(N, flags) == N);                                               \
                                                                                                    \
    for (unsigned i = 0; i < N; ++i) {                                                              \
        uflags_assert(!uflags_is_set(N, flags, uflags_bit(N, i)));                                  \
    }                                                                                               \
                                                                                                    \
    flags = uflags_all(N);                                                                          \
    uflags_assert(flags != 0);                                                                      \
    uflags_assert(uflags_count_set(N, flags) == N);                                                 \
    uflags_assert(uflags_count_unset(N, flags) == 0);                                               \
                                                                                                    \
    for (unsigned i = 0; i < N; ++i) {                                                              \
        uflags_assert(uflags_is_set(N, flags, uflags_bit(N, i)));                                   \
    }                                                                                               \
                                                                                                    \
    flags = uflags_bit(N, (N - 2));                                                                 \
    uflags_assert(flags != 0);                                                                      \
    uflags_assert(uflags_count_set(N, flags) == 1);                                                 \
    uflags_assert(uflags_count_unset(N, flags) == (N - 1));                                         \
                                                                                                    \
    for (unsigned i = 0; i < N; ++i) {                                                              \
        if (i == (N - 2)) {                                                                         \
            uflags_assert(uflags_is_set(N, flags, uflags_bit(N, i)));                               \
        } else {                                                                                    \
            uflags_assert(!uflags_is_set(N, flags, uflags_bit(N, i)));                              \
        }                                                                                           \
    }                                                                                               \
                                                                                                    \
    uflags_set(N, flags, uflags_bit(N, 1));                                                         \
    uflags_assert(flags != 0);                                                                      \
    uflags_assert(uflags_count_set(N, flags) == 2);                                                 \
    uflags_assert(uflags_count_unset(N, flags) == (N - 2));                                         \
                                                                                                    \
    for (unsigned i = 0; i < N; ++i) {                                                              \
        if (i == 1 || i == (N - 2)) {                                                               \
            uflags_assert(uflags_is_set(N, flags, uflags_bit(N, i)));                               \
        } else {                                                                                    \
            uflags_assert(!uflags_is_set(N, flags, uflags_bit(N, i)));                              \
        }                                                                                           \
    }                                                                                               \
                                                                                                    \
    uflags_assert(uflags_is_any_set(N, flags, uflags_bit(N, 1) | uflags_bit(N, (N - 1))));          \
    uflags_assert(!uflags_is_any_set(N, flags, uflags_bit(N, 2) | uflags_bit(N, (N - 1))));         \
                                                                                                    \
    uflags_unset(N, flags, uflags_bit(N, 1));                                                       \
    uflags_assert(!uflags_is_set(N, flags, uflags_bit(N, 1)));                                      \
                                                                                                    \
    uflags_toggle(N, flags, uflags_bit(N, 1));                                                      \
    uflags_assert(uflags_is_set(N, flags, uflags_bit(N, 1)));                                       \
                                                                                                    \
    uflags_toggle(N, flags, uflags_bit(N, 1));                                                      \
    uflags_assert(!uflags_is_set(N, flags, uflags_bit(N, 1)));                                      \
                                                                                                    \
    return true;                                                                                    \
}

static bool test_flags_8(void) uflags_test_impl(8)
static bool test_flags_16(void) uflags_test_impl(16)
static bool test_flags_32(void) uflags_test_impl(32)
static bool test_flags_64(void) uflags_test_impl(64)

int main(void) {
    printf("Starting tests...\n");

    int exit_code = EXIT_SUCCESS;
    bool (*tests[])(void) = {
        test_flags_8,
        test_flags_16,
        test_flags_32,
        test_flags_64
    };

    for (uint32_t i = 0; i < array_size(tests); ++i) {
        if (!tests[i]()) exit_code = EXIT_FAILURE;
    }

    if (exit_code == EXIT_SUCCESS) {
        printf("All tests passed.\n");
    } else {
        printf("Some tests failed.\n");
    }

    return exit_code;
}
