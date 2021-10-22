#pragma once


#if defined(__GNUC__)
#  define D_FORCE_INLINE __attribute__ ((always_inline))
#elif defined(_MSC_VER)
#  define D_FORCE_INLINE __forceinline
#endif

#include <type_traits>

#define __FAST_RUNTIME_TYPE_CASTING_REMOVE_POINTER_T(POINTER_TYPE) std::remove_pointer_t<POINTER_TYPE>
#define __FAST_RUNTIME_TYPE_CASTING_IS_POINTER_TYPE(POINTER_TYPE) std::is_pointer_v<POINTER_TYPE>

#define __FAST_RUNTIME_TYPE_CASTING_CONCAT(STR1, STR2) STR1##STR2
#define __FAST_RUNTIME_TYPE_CASTING_MAKE_STRING(STR) #STR