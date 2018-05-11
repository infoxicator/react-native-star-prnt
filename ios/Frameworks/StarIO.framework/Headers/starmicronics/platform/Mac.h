#ifndef platform_mac__
#define platform_mac__

#include <sys/types.h>
//#include <ppc/types.h>
#include <limits.h>

#define DLL_EXPORT __attribute__((visibility("default")))
#define DLL_IMPORT

#define STARMICRONICS_API

#define CALL_CONVENT

#ifndef SM_BOOLEAN
  #define SM_BOOLEAN u_int32_t
#endif
#define SM_TRUE ((u_int32_t) (1 == 1))
#define SM_FALSE ((u_int32_t) (0 > 1))

#define UCHAR  u_int8_t
#define MAX_UCHAR ((UCHAR) UCHAR_MAX)

#define UINT16 u_int16_t
#define MAX_UINT16 ((UINT16) USHRT_MAX)

#define UINT32 u_int32_t
#define MAX_UINT32 ((UINT32) UINT_MAX)

#define UINT64 u_int64_t
#define MAX_UINT64 ((UINT64) ULLONG_MAX)

#define CHAR   int8_t
#define MIN_CHAR ((CHAR) CHAR_MIN)
#define MAX_CHAR ((CHAR) CHAR_MAX)

#define INT16  int16_t
#define MIN_INT16 ((INT16) SHRT_MIN)
#define MAX_INT16 ((INT16) SHRT_MAX)

#define INT32  int32_t
#define MIN_INT32 ((INT32) INT_MIN)
#define MAX_INT32 ((INT32) INT_MAX)

#define INT64  int64_t
#define MIN_INT64 ((INT64) LLONG_MIN)
#define MAX_INT64 ((INT64) LLONG_MAX)

#define FLOAT  float
#define MIN_FLOAT __FLT_MIN__
#define MAX_FLOAT __FLT_MAX__

#define DOUBLE double
#define MIN_DOUBLE __DBL_MIN__
#define MAX_DOUBLE __DBL_MAX__

#define PATH_SEPERATOR_CHAR '/'
#define PATH_SEPERATOR_STRING "/"

#endif
