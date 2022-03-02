#include "common.h"
#include "sa.h"
#include "sa_mm.h"

/**
 * @file
 * @brief Socket address factory.
 */

/**
 * @brief Creates an AF_UNSPEC socket address.
 * @attention Caller should use sa_free(sa) to clean up.
 * @param port A port number to use.
 * @return NULL on failure, otherwise a pointer to the created socket address.
 * @public
 */
struct sockaddr *sa_unspec(uint16_t port) {
    struct sockaddr_in6 *sa = sa_alloc(sizeof(struct sockaddr_in6));
    if (sa == NULL) return NULL;

    sa->sin6_family = AF_UNSPEC;
    sa->sin6_port = htons(port);
    return (struct sockaddr *) sa;
}

/**
 * @brief Creates an AF_INET socket address.
 * @attention Caller should use sa_free(sa) to clean up.
 * @param str A IPv4 string to parse.
 * @param port A port number to use.
 * @return NULL on failure, otherwise a pointer to the created socket address.
 * @public
 */
struct sockaddr *sa_ipv4(const char *str, uint16_t port) {
    if (str == NULL) return NULL;

    struct sockaddr_in *sa = sa_alloc(sizeof(struct sockaddr_in));
    if (sa == NULL) return NULL;

    if (inet_pton(AF_INET, str, &sa->sin_addr) != 1) {
        sa_free(sa);
        return NULL;
    }
    sa->sin_family = AF_INET;
    sa->sin_port = htons(port);
    return (struct sockaddr *) sa;
}

/**
 * @brief Creates an AF_INET socket address.
 * @attention Caller should use sa_free(sa) to clean up.
 * @param address A IPv4 address in network byte order.
 * @param port A port number to use.
 * @return NULL on failure, otherwise a pointer to the created socket address.
 * @public
 */
struct sockaddr *sa_ipv4_bin(const uint8_t *address, uint16_t port) {
    if (address == NULL) return NULL;

    struct sockaddr_in *sa = sa_alloc(sizeof(struct sockaddr_in));
    if (sa == NULL) return NULL;

    sa->sin_family = AF_INET;
    sa->sin_addr = *(struct in_addr*)address;
    sa->sin_port = htons(port);
    return (struct sockaddr *) sa;
}

/**
 * @brief Creates an AF_INET6 socket address.
 * @attention Caller should use sa_free(sa) to clean up.
 * @param str A IPv6 string to parse.
 * @param port A port number to use.
 * @return NULL on failure, otherwise a pointer to the created socket address.
 * @public
 */
struct sockaddr *sa_ipv6(const char *str, uint16_t port) {
    if (str == NULL) return NULL;

    struct sockaddr_in6 *sa = sa_alloc(sizeof(struct sockaddr_in6));
    if (sa == NULL) return NULL;

    if (inet_pton(AF_INET6, str, &sa->sin6_addr) != 1) {
        sa_free(sa);
        return NULL;
    }
    sa->sin6_family = AF_INET6;
    sa->sin6_port = htons(port);
    return (struct sockaddr *) sa;
}

/**
 * @brief Creates an AF_INET6 socket address.
 * @attention Caller should use sa_free(sa) to clean up.
 * @param address A IPv6 address in network byte order.
 * @param port A port number to use.
 * @return NULL on failure, otherwise a pointer to the created socket address.
 * @public
 */
struct sockaddr *sa_ipv6_bin(const uint8_t *address, uint16_t port) {
    if (address == NULL) return NULL;

    struct sockaddr_in6 *sa = sa_alloc(sizeof(struct sockaddr_in6));
    if (sa == NULL) return NULL;

    sa->sin6_family = AF_INET6;
    sa->sin6_addr = *(struct in6_addr*)address;
    sa->sin6_port = htons(port);
    return (struct sockaddr *) sa;
}