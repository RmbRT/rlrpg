#ifndef __rlrpg_defines_hpp_defined
#define __rlrpg_defines_hpp_defined

#ifdef _MSC_VER
#define forceinline __forceinline
#else
#define forceinline inline
#endif

#ifndef _countof
#define _countof(x) (sizeof((x)) / sizeof((x)[0]))
#endif

#define rlrpg_last(name) name, __last = name
#define rlrpgenumcount(name) (1+(int)name::__last)

#endif