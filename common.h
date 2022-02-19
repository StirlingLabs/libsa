#include <stdlib.h>

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
