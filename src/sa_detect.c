#include "common.h"
#include "sa.h"
/**
 * @file
 * @brief Socket address detection capability. 
 */

/**
 * @brief Identifies socket addresses that are AF_UNSPEC.
 * @param sa Pointer to a socket address.
 * @return non-zero if the @param sa is AF_UNSPEC.
 * @public
 */
SA_BOOL sa_is_unspec(struct sockaddr *sa) {
    if (sa == NULL) return 0;
    return sa->sa_family == AF_UNSPEC;
}

/**
 * @brief Identifies socket addresses that are AF_INET.
 * @param sa Pointer to a socket address.
 * @return non-zero if the @param sa is AF_INET.
 * @public
 */
SA_BOOL sa_is_ipv4(struct sockaddr *sa) {
    if (sa == NULL) return 0;
    return sa->sa_family == AF_INET;
}

/**
 * @brief Identifies socket addresses that are AF_INET6.
 * @param sa Pointer to a socket address.
 * @return non-zero if the @param sa is AF_INET6.
 * @public
 */
SA_BOOL sa_is_ipv6(struct sockaddr *sa) {
    if (sa == NULL) return 0;
    return sa->sa_family == AF_INET6;
}
