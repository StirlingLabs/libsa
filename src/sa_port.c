#include "common.h"
#include "sa.h"

/**
 * @file
 * @brief Socket address port definition.
 */

/**
 * @private
 */
INLINE int _sa_get_ipv4_port(struct sockaddr_in *sa) {
    if (sa == NULL) return -1;

    return ntohs(sa->sin_port);
}

/**
 * @private
 */
INLINE int _sa_get_ipv6_port(struct sockaddr_in6 *sa) {
    if (sa == NULL) return -1;

    return ntohs(sa->sin6_port);
}

/**
 * @brief Gets the port of a socket address.
 * @param sa Pointer to a socket address.
 * @return -1 on failure, otherwise a port number.
 * @public
 */
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

/**
 * @private
 */
INLINE SA_BOOL _sa_set_port4(struct sockaddr_in *sa, uint16_t port) {
    sa->sin_port = htons(port);
    return 1;
}

/**
 * @private
 */
INLINE SA_BOOL _sa_set_port6(struct sockaddr_in6 *sa, uint16_t port) {
    sa->sin6_port = htons(port);
    return 1;
}

/**
 * @brief Sets the port of a socket address.
 * @param sa Pointer to a socket address.
 * @param port A port number to use.
 * @return Non-zero on success.
 * @public
 */
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