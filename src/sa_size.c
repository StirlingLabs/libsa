#include "common.h"
#include "sa.h"
/**
 * @file
 * @brief Get the size of the sockaddr in various circumstances.
 */

/**
 * @brief Gets the copyable size of the socket address.
 * @param sa Pointer to a socket address.
 * @return Zero if unknown, otherwise the relevant copyable size.
 * @public
 */
size_t sa_get_size(struct sockaddr *sa) {
    switch (sa->sa_family) {
        case AF_INET:
            return sizeof(struct sockaddr_in);

        case AF_UNSPEC:
        case AF_INET6:
            return sizeof(struct sockaddr_in6);
    }

    return sizeof(struct sockaddr_storage);
}

 /**
 * @brief Gets the copyable size of a socket address of a given family.
 * @attention This is provided for advanced use at the user's discretion.
 * @param family A platform specific address family.
 * @return The size of a sockaddr_storage structure if unknown, otherwise the relevant copyable size.
 * @public
 */
 size_t sa_get_size_by_family(uint16_t family) {
    switch (family) {
        case AF_INET:
            return sizeof(struct sockaddr_in);

        case AF_UNSPEC:
        case AF_INET6:
            return sizeof(struct sockaddr_in6);
    }

    return sizeof(struct sockaddr_storage);
}

/**
 * @brief Gets the copyable size of a sockaddr_storage structure.
 * @attention The return value may be treated as constant.
 * @return The copyable size.
 * @public
 */
size_t sa_get_size_storage() {
    return sizeof(struct sockaddr_storage);
}

/**
 * @brief Gets a generally safe copyable size of an unspecified family sockaddr structure.
 * @attention The return value may be treated as constant.
 * @return The copyable size.
 * @public
 */
size_t sa_get_size_unspec() {
    return sizeof(struct sockaddr_in6);
}

/**
 * @brief Gets the copyable size of a sockaddr_in structure.
 * @attention The return value may be treated as constant.
 * @return The copyable size.
 * @public
 */
size_t sa_get_size_ipv4() {
    return sizeof(struct sockaddr_in);
}

/**
 * @brief Gets the copyable size of a sockaddr_in6 structure.
 * @attention The return value may be treated as constant.
 * @return The copyable size.
 * @public
 */
size_t sa_get_size_ipv6() {
    return sizeof(struct sockaddr_in6);
}
