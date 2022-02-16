#if _WIN32

#include <ws2tcpip.h>
#include <netioapi.h>

#else

#include <sys/socket.h>
#include <net/if.h>

#endif