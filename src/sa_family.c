#include "common.h"
#include "sa.h"

/**
 * @file
 * @brief Socket address family definition. 
 */

/**
 * @brief Sets the platform specific address family of a socket address.
 * @attention This is provided for advanced use at the user's discretion.
 * @param sa Pointer to a socket address.
 * @param family A platform specific address family value to specify.
 * @return Non-zero on success.
 * @public
 */
SA_BOOL sa_set_family(struct sockaddr *sa, int family) {
    if (sa == NULL) return 0;
    sa->sa_family = family;
    return 1;
}

/**
 * @brief Gets the platform specific address family of a socket address.
 * @attention This is provided for advanced use at the user's discretion.
 * @param sa Pointer to a socket address.
 * @return -1 on failure, otherwise the platform specific address family value.
 * @public
 */
int sa_get_family(const struct sockaddr *sa) {
    return sa->sa_family;
}

/**
 * @brief Detects if the socket address structure has a length field.
 * @attention This is provided for advanced use at the user's discretion.
 * @return Non-zero when true.
 * @public
 */
SA_BOOL sa_has_len_field(void) {
#if HAVE_SOCKADDR_SA_LEN
    return 1;
#else
    return offsetof(struct sockaddr, sa_family) != 0;
#endif
}

/**
 * @brief Detects the address family field offset.
 * @attention This is provided for advanced use at the user's discretion.
 * @return The offset of the address family field in the socket address structure.
 * @public
 */
ptrdiff_t sa_family_offset(void) {
    return offsetof(struct sockaddr, sa_family);
}

/**
 * @brief Gets the platform specific address family of an unspecified (AF_UNSPEC) socket address.
 * @attention This is provided for advanced use at the user's discretion.
 * @return -1 on failure, otherwise the platform specific address family value.
 * @public
 */
int sa_get_family_unspec() {
    return AF_UNSPEC;
}

/**
 * @brief Gets the platform specific address family of an IPv4 (AF_INET) socket address.
 * @attention This is provided for advanced use at the user's discretion.
 * @return -1 on failure, otherwise the platform specific address family value.
 * @public
 */
int sa_get_family_ipv4() {
    return AF_INET;
}

/**
 * @brief Gets the platform specific address family of an IPv6 (AF_INET6) socket address.
 * @attention This is provided for advanced use at the user's discretion.
 * @return -1 on failure, otherwise the platform specific address family value.
 * @public
 */
int sa_get_family_ipv6() {
    return AF_INET6;
}