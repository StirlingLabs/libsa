#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdalign.h>
#include <assert.h>

/*! @typedef intptr2_t 
 * A type that is 2 pointer-sized primitives.
 */
#if INTPTR_MAX == INT64_MAX
#if defined(_MSC_VER)
typedef struct intptr2 {
    alignas(sizeof(intptr_t)*2)
    intptr_t a;
    intptr_t b;
} intptr2_t;
#else
typedef __int128 intptr2_t;
#endif
#else
typedef int64_t intptr2_t;
#endif

static_assert(sizeof(intptr2_t) == sizeof(intptr_t) * 2, "must be the size of 2 intptr_t");
static_assert(alignof(intptr2_t) == sizeof(intptr_t) * 2, "must be the alignment of 2 intptr_t");

#if defined(_MSC_VER)

#include <intrin.h>

__forceinline
bool cas(intptr2_t *target, intptr2_t *comparand, intptr2_t *exchange) {
    intptr2_t desired = *exchange;
#if _WIN64
    return _InterlockedCompareExchange128(
            (volatile __int64 *) target,
            desired.b,
            desired.a,
            (__int64 *) comparand
    );
#else
    return _InterlockedCompareExchange64(
        target,
        *desired,
        comparand
    );
#endif
}

__forceinline
intptr2_t cas_read(intptr2_t *target) {
    intptr2_t actual = {0};
#if _WIN64
    _InterlockedCompareExchange128(
            (volatile __int64 *) target,
            actual.b,
            actual.a,
            (__int64 *) &actual
    );
    return actual;
#else
    __InterlockedCompareExchange64(
        target,
        actual,
        &actual
    );
    return actual;
#endif
}

#elif defined(__INTEL_COMPILER)

#include <stdatomic.h>

__attribute__((always_inline, flatten)) inline
bool cas(intptr2_t * target, intptr2_t * comparand, intptr2_t * exchange) {
    intptr2_t desired = *comparand;
    return atomic_compare_exchange_strong(target, &desired, *exchange);
}

__attribute__((always_inline, flatten)) inline
intptr2_t cas_read(intptr2_t * target) {
    return atomic_load(target);
}

#elif defined(__GNUC__) || defined(__clang__)

#include <stdatomic.h>

// gcc, clang
// compare: atomic_compare_exchange_weak, atomic_compare_exchange_strong
__attribute__((always_inline, flatten)) inline
bool cas(intptr2_t *target, intptr2_t *comparand, intptr2_t *exchange) {
#ifdef __aarch64__
    // based on atomic.cc from Google's Fuchsia under MIT
    // this is an implementation with the strongest semantics

    volatile intptr2_t *ptr = (volatile intptr2_t *) target;
    intptr2_t *expected = (intptr2_t *) comparand;
    int result;
    do {
        uint64_t temp_lo;
        uint64_t temp_hi;
        __asm__ volatile(
                "ldaxp %[lo], %[hi], %[src]"
                : [ lo ] "=r"(temp_lo)
                , [ hi ] "=r"(temp_hi)
        : [ src ] "Q"(*ptr)
        : "memory"
        );
        intptr2_t temp = ((intptr2_t) temp_hi) << 64 | temp_lo;

        if (temp != *expected) {
            // No reason to leave the monitor in Exclusive so clear it.
            __asm__ volatile("clrex");
            *expected = temp;
            return false;
        }

        intptr_t desired_lo = (intptr_t) (*exchange);
        intptr_t desired_hi = (intptr_t) (*exchange >> 64);
        __asm__ volatile(
                "stlxp %w[result], %[lo], %[hi], %[ptr]"
                : [ result ] "=&r"(result)
                , [ ptr ] "=Q"(*ptr)
        : [ lo ] "r"(desired_lo)
                , [ hi ] "r"(desired_hi)
        : "memory"
        );
    } while (result);
    return true;
#else
#if defined(__i386__) || defined(__x86_64__)
    bool result = false;
    intptr_t a = (intptr_t) *comparand;
    intptr_t d = (intptr_t) (*comparand >> (sizeof(intptr_t) * 8));
    intptr_t c = (intptr_t) (*exchange >> (sizeof(intptr_t) * 8));
    intptr_t b = (intptr_t) *exchange;
#if INTPTR_MAX == INT64_MAX
    __asm__ __volatile__
    (
        "lock cmpxchg16b %0"
        : "+m" ( *target ) // address
        , "=@ccz" ( result ) // equal flag
        , "+a" (a) // rax
        , "+d" (d) // rdx
        : "b" (b) // rbx
        , "c" (c) // rcx
        : "cc", "memory"
    );
#else
    __asm__ __volatile__
    (
        "lock cmpxchg8b %0"
        : "+m" ( *target ) // address
        , "=@ccz" ( result ) // equal flag
        , "+a" (a) // eax
        , "+d" (d) // edx
        : "b" (b) // ebx
        , "c" (c) // ecx
        : "cc", "memory"
    );
#endif
    return result;
#else
    p2_t desired = *comparand;
    return atomic_compare_exchange_strong((_Atomic intptr2_t*)target, &desired, *exchange);
#endif
#endif
}

__attribute__((always_inline, flatten)) inline
intptr2_t cas_read(intptr2_t * target) {
#ifdef __aarch64__
    // based on atomic.cc from Google's Fuchsia under MIT
    // this is an implementation with the strongest semantics
    volatile intptr2_t* ptr = (volatile intptr2_t*)(target);
    intptr_t value_lo;
    intptr_t value_hi;
    int result;
    do {
    __asm__ volatile("ldaxp %[lo], %[hi], %[ptr]"
         : [ lo ] "=r"(value_lo), [ hi ] "=r"(value_hi)
         : [ ptr ] "Q"(*ptr));
    __asm__ volatile("stlxp %w[result], %[lo], %[hi], %[ptr]"
         : [ result ] "=&r"(result), [ ptr ] "=Q"(*ptr)
         : [ lo ] "r"(value_lo), [ hi ] "r"(value_hi)
         : "memory");
    } while (result);
    return (((intptr2_t)(value_hi)) << (sizeof(intptr_t)*8)) | value_lo;
#else
#if defined(__i386__) || defined(__x86_64__)
    intptr_t a = 0;
    intptr_t d = 0;
    intptr_t c = 0;
    intptr_t b = 0;
#if INTPTR_MAX == INT64_MAX
    __asm__ __volatile__
    (
        "lock cmpxchg16b %0"
        : "+m" ( *target ) // address
        , "+a" (a) // rax
        , "+d" (d) // rdx
        : "b" (b) // rbx
        , "c" (c) // rcx
        : "cc", "memory"
    );
#else
    __asm__ __volatile__
    (
        "lock cmpxchg8b %0"
        : "+m" ( *target ) // address
        , "+a" (a) // eax
        , "+d" (d) // edx
        : "b" (b) // ebx
        , "c" (c) // ecx
        : "cc", "memory"
    );
#endif
    return (((intptr2_t)d) << (sizeof(intptr_t)*8)) | a;
#else
    return atomic_load((_Atomic intptr2_t*)target);
#endif
#endif
}

#endif

#define intptr2_sub(name, i) \
    ((intptr_t*)&name)[i]

#define intptr2_dcl(name) \
    intptr2_t name

#define intptr2_def(name, a, b) \
    intptr2_t_dcl(name); \
    intptr2_t_sub(name, 0) = a; \
    intptr2_t_sub(name, 1) = b

