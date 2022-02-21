#pragma once

// this is just a toy for future use with xch_sa_mm_fns
// missing: arm64 impl on non-win

#if defined(_MSC_VER)

#include <intrin.h>

#elif defined(__clang__)
// TODO: validate
_Bool
_InterlockedCompareExchange128(
    int64_t volatile *Destination,
    int64_t ExchangeHigh,
    int64_t ExchangeLow,
    int64_t *ComparandResult
    )
{
    _Bool Matched;
  __asm__ __volatile__
    (
        "lock cmpxchg16b %1\n\t"
        "setz %0"
        : "=q" ( Matched )
        , "+m" ( *Destination )
        , "+d" ( ComparandResult[1] )
        , "+a" ( ComparandResult[0] )
        : "c" ( ExchangeHigh )
        , "b" ( ExchangeLow )
        : "cc", "memory"
    );
  return Matched;
}
#else
// TODO: validate
_Bool
_InterlockedCompareExchange128(
    int64_t volatile *Destination,
    int64_t ExchangeHigh,
    int64_t ExchangeLow,
    int64_t *ComparandResult
    )
{
    _Bool Matched;
  __asm__ __volatile__
  (
      "lock cmpxchg16b %1"
      : "=ccz" ( Matched )
      , "+m" ( *Destination )
      , "+d" ( ComparandResult[1] )
      , "+a" ( ComparandResult[0] )
      : "c" ( ExchangeHigh )
      , "b" ( ExchangeLow )
      : "cc", "memory"
  );
  return Matched;
}
#endif

#define CAS128 _InterlockedCompareExchange128


// todo: xplat CAS64 for 32-bit platforms
