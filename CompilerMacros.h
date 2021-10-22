#pragma once


#if defined(__GNUC__)
#  define D_FORCE_INLINE __attribute__ ((always_inline))
#elif defined(_MSC_VER)
#  define D_FORCE_INLINE __forceinline
#endif