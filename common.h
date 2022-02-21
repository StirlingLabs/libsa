#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#if _WIN32

#include <ws2tcpip.h>
#include <netioapi.h>

#else

#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <net/if.h>

#endif

#ifndef _DEBUG
#if defined(_MSC_VER) && !__INTEL_COMPILER && _MSC_VER >= 1310
#define INLINE __forceinline
#elif __GNUC__ || __has_attribute(always_inline)
#define INLINE __attribute__((always_inline))
#else
#define INLINE inline
#endif
#else
#define INLINE
#endif