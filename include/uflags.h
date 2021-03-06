/**
 * uFlags - collection of C primitives to safely manipulate bitmasks.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2020 Ivano Bilenchi
 * @copyright <https://ivanobilenchi.com>
 * @copyright SPDX-License-Identifier: MIT
 *
 * @file
 */

#ifndef UFLAGS_H
#define UFLAGS_H

#include <limits.h>
#include <stdint.h>

// ###############
// # Public API #
// ###############

/**
 * Bitmask manipulation API.
 *
 * @note This is not a real data structure, though it is declared as such
 *       for better grouping in the generated documentation.
 *
 * @struct UFlags
 */

/**
 * Bitmask type.
 *
 * @param N Bitmask size in bits. Allowed values: 8, 16, 32 and 64.
 *
 * @public @related UFlags
 */
#define UFlags(N) P_UFLAGS_MACRO_CONCAT(P_UFLAGS_MACRO_CONCAT(uint, N), _t)

/**
 * Bitmask with all bits set to zero.
 *
 * @param N Bitmask size in bits.
 * @return Bitmask with all bits set to zero.
 *
 * @public @related UFlags
 */
#define uflags_none(N) ((UFlags(N))0)

/**
 * Bitmask with all bits set to one.
 *
 * @param N Bitmask size in bits.
 * @return Bitmask with all bits set to one.
 *
 * @public @related UFlags
 */
#define uflags_all(N) ((UFlags(N))~uflags_none(N))

/**
 * Returns a bitmask with the specified bit set.
 *
 * @param N Bitmask size in bits.
 * @param BIT Bit to set.
 * @return Bitmask with the specified bit set.
 *
 * @public @related UFlags
 */
#define uflags_bit(N, BIT) P_UFLAGS_MACRO_CONCAT(p_uflags_bit_, N)(BIT)

/**
 * Checks whether a bitmask has specific bits set.
 *
 * @param N Bitmask size in bits.
 * @param FLAGS Bitmask.
 * @param FLAG Bit(s) to check.
 * @return True if the bits are set, false otherwise.
 *
 * @public @related UFlags
 */
#define uflags_is_set(N, FLAGS, FLAG) \
    (((FLAGS) & (UFlags(N))(FLAG)) == (UFlags(N))(FLAG))

/**
 * Checks whether a bitmask has any of the specified bits set.
 *
 * @param N Bitmask size in bits.
 * @param FLAGS Bitmask.
 * @param FLAG Bit(s) to check.
 * @return True if at least one of the specified bits is set, false otherwise.
 *
 * @public @related UFlags
 */
#define uflags_is_any_set(N, FLAGS, FLAG) (((FLAGS) & (UFlags(N))(FLAG)) != 0)

/**
 * Sets bits in a bitmask.
 *
 * @param N Bitmask size in bits.
 * @param FLAGS Bitmask.
 * @param FLAG Bit(s) to set.
 *
 * @public @related UFlags
 */
#define uflags_set(N, FLAGS, FLAG) ((FLAGS) |= (UFlags(N))(FLAG))

/**
 * Unsets bits in a bitmask.
 *
 * @param N Bitmask size in bits.
 * @param FLAGS Bitmask.
 * @param FLAG Bit(s) to unset.
 *
 * @public @related UFlags
 */
#define uflags_unset(N, FLAGS, FLAG) ((FLAGS) &= (UFlags(N))(~(UFlags(N))(FLAG)))

/**
 * Sets or unsets bits in a bitmask.
 *
 * @param N Bitmask size in bits.
 * @param FLAGS Bitmask.
 * @param FLAG Bit(s) to set or unset.
 * @param BOOL True to set, false to unset.
 *
 * @public @related UFlags
 */
#define uflags_set_bool(N, FLAGS, FLAG, BOOL) \
    ((BOOL) ? uflags_set(N, FLAGS, FLAG) : uflags_unset(N, FLAGS, FLAG))

/**
 * Toggles bits in a bitmask.
 *
 * @param N Bitmask size in bits.
 * @param FLAGS Bitmask.
 * @param FLAG Bit(s) to toggle.
 *
 * @public @related UFlags
 */
#define uflags_toggle(N, FLAGS, FLAG) ((FLAGS) ^= (UFlags(N))(FLAG))

/**
 * Returns the number of bits that are set in a bitmask.
 *
 * @param N Bitmask size in bits.
 * @param FLAGS Bitmask.
 * @return Number of set bits.
 *
 * @public @related UFlags
 */
#define uflags_count_set(N, FLAGS) P_UFLAGS_MACRO_CONCAT(p_uflags_count_set_, N)(FLAGS)

/**
 * Returns the number of bigs that are not set in a bitmask.
 *
 * @param N Bitmask size in bits.
 * @param FLAGS Bitmask.
 * @return Number of unset bits.
 *
 * @public @related UFlags
 */
#define uflags_count_unset(N, FLAGS) ((N) - uflags_count_set(N, FLAGS))

// ###############
// # Private API #
// ###############

#define P_UFLAGS_MACRO_CONCAT(a, b) P_UFLAGS_MACRO_CONCAT_INNER(a, b)
#define P_UFLAGS_MACRO_CONCAT_INNER(a, b) a##b

#define p_uflags_bit_8(BIT) ((unsigned)1 << (unsigned)(BIT))
#define p_uflags_bit_16(BIT) ((unsigned)1 << (unsigned)(BIT))
#define p_uflags_bit_32(BIT) ((UFlags(32))1 << (unsigned)(BIT))
#define p_uflags_bit_64(BIT) ((UFlags(64))1 << (unsigned)(BIT))

#if !defined(UFLAGS_NO_BUILTINS) && defined(__GNUC__)

#define p_uflags_count_set_8(FLAGS) __builtin_popcount(FLAGS)
#define p_uflags_count_set_16(FLAGS) __builtin_popcount(FLAGS)
#define p_uflags_count_set_32(FLAGS) __builtin_popcountl(FLAGS)
#define p_uflags_count_set_64(FLAGS) __builtin_popcountll(FLAGS)

#else

#define p_uflags_count_set_def(N)                                                                   \
static inline unsigned p_uflags_count_set_##N(UFlags(N) flags) {                                    \
    flags = flags - ((UFlags(N))(flags >> 1U) & (UFlags(N))(uflags_all(N) / 3));                    \
    flags = (flags & (UFlags(N))(uflags_all(N) / 15 * 3)) +                                         \
            ((UFlags(N))(flags >> 2U) & (UFlags(N))(uflags_all(N) / 15 * 3));                       \
    flags = (UFlags(N))(flags + (flags >> 4U)) & (UFlags(N))(uflags_all(N) / 255 * 15);             \
    flags = (UFlags(N))(flags * (uflags_all(N) / 255)) >> (UFlags(N))((N) - CHAR_BIT);              \
    return (unsigned)flags;                                                                         \
}

#ifdef __cplusplus
extern "C" {
#endif

p_uflags_count_set_def(8)
p_uflags_count_set_def(16)
p_uflags_count_set_def(32)
p_uflags_count_set_def(64)

#ifdef __cplusplus
}
#endif

#endif

#endif // UFLAGS_H
