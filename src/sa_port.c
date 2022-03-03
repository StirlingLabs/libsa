#include "common.h"
#include "sa.h"

INLINE int _sa_get_ipv4_port(struct sockaddr_in *sa) {
    if (sa == NULL) return -1;

    return ntohs(sa->sin_port);
}

INLINE int _sa_get_ipv6_port(struct sockaddr_in6 *sa) {
    if (sa == NULL) return -1;

    return ntohs(sa->sin6_port);
}

int sa_get_port(struct sockaddr *sa) {
    if (sa == NULL) return -1;

    switch (sa->sa_family) {

        case AF_INET:
            return _sa_get_ipv4_port((struct sockaddr_in *) sa);

        case AF_UNSPEC:
        case AF_INET6:
            return _sa_get_ipv6_port((struct sockaddr_in6 *) sa);

    }

    return -1;
}

INLINE SA_BOOL _sa_set_port4(struct sockaddr_in *sa, uint16_t port) {
    sa->sin_port = htons(port);
    return 1;
}

INLINE SA_BOOL _sa_set_port6(struct sockaddr_in6 *sa, uint16_t port) {
    sa->sin6_port = htons(port);
    return 1;
}

SA_BOOL sa_set_port(struct sockaddr *sa, uint16_t port) {
    if (sa == NULL) return 0;

    switch (sa->sa_family) {

        case AF_INET:
            return _sa_set_port4((struct sockaddr_in *) sa, port);

        case AF_INET6:
            return _sa_set_port6((struct sockaddr_in6 *) sa, port);

    }

    return 0;
}