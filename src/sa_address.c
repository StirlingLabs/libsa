#include "common.h"
#include "sa.h"

/**
 * @file
 * @brief Socket address... address definition. 
 */

/**
 * @private
 */
int _sa_get_ipv4_byte(struct sockaddr_in *sa, size_t offset) {
    if (offset >= sizeof(struct in_addr)) return -1;
    return ((uint8_t *) &sa->sin_addr)[offset];
}

/**
 * @private
 */
int _sa_get_ipv6_byte(struct sockaddr_in6 *sa, size_t offset) {
    if (offset >= sizeof(struct in6_addr)) return -1;
    return ((uint8_t *) &sa->sin6_addr)[offset];
}

/**
 * @brief Gets a byte from the address part of the socket address structure.
 * @param sa Pointer to a socket address.
 * @param offset An offset into the address.
 * @return -1 on failure, otherwise the value of the read byte.
 * @public
 */
int sa_get_address_byte(struct sockaddr *sa, size_t offset) {
    if (sa == NULL) return -1;

    switch (sa->sa_family) {

        case AF_INET:
            return _sa_get_ipv4_byte((struct sockaddr_in *) sa, offset);

        case AF_INET6:
            return _sa_get_ipv6_byte((struct sockaddr_in6 *) sa, offset);

    }

    return -1;
}

/**
 * @private
 */
SA_BOOL _sa_set_ipv4_byte(struct sockaddr_in *sa, size_t offset, uint8_t value) {
    if (offset >= sizeof(struct in_addr)) return 0;
    ((uint8_t *) &sa->sin_addr)[offset] = value;
    return 1;
}

/**
 * @private
 */
SA_BOOL _sa_set_ipv6_byte(struct sockaddr_in6 *sa, size_t offset, uint8_t value) {
    if (offset >= sizeof(struct in6_addr)) return 0;
    ((uint8_t *) &sa->sin6_addr)[offset] = value;
    return 1;
}

/**
 * @brief Sets a byte within the address part of the socket address structure.
 * @param sa Pointer to a socket address.
 * @param offset An offset into the address.
 * @param value The byte value to write.
 * @return Non-zero on success.
 * @public
 */
SA_BOOL sa_set_address_byte(struct sockaddr *sa, size_t offset, uint8_t value) {
    if (sa == NULL) return 0;

    switch (sa->sa_family) {

        case AF_INET:
            return _sa_set_ipv4_byte((struct sockaddr_in *) sa, offset, value);

        case AF_INET6:
            return _sa_set_ipv6_byte((struct sockaddr_in6 *) sa, offset, value);

    }

    return 0;
}

/**
 * @brief Allows direct memory access to the address bytes of a socket address. 
 * @param sa Pointer to a socket address.
 * @param size Reports the count of bytes that make up the memory region.
 * @return Null on failure, otherwise a pointer to the address bytes of a socket address.
 * @public
 */
const uint8_t *sa_address_bytes(struct sockaddr *sa, size_t *size) {
    if (sa == NULL) return NULL;
    if (size == NULL) return NULL;

    switch (sa->sa_family) {

        case AF_INET:
            *size = sizeof(struct in_addr);
            return (uint8_t *) &((struct sockaddr_in *) sa)->sin_addr;

        case AF_INET6:
            *size = sizeof(struct in6_addr);
            return (uint8_t *) &((struct sockaddr_in6 *) sa)->sin6_addr;

    }

    return NULL;
}
