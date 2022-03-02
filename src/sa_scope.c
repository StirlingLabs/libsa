#include "common.h"
#include "sa.h"
#include "sa_mm.h"
/**
 * @file
 * @brief Socket address scope definition. 
 */


/**
 * @brief Gets the name of a scope (network interface) index.
 * @param scope The index of a scope (network interface).
 * @return The name of the scope (network interface).
 * @public
 */
const char *sa_scope_get_name(uint16_t scope) {
    if (scope == 0) return NULL;

    char *s = sa_alloc(IF_NAMESIZE);
    if (s == NULL) return NULL;

    const char *n = if_indextoname(scope, s);
    if (n == NULL) {
        sa_free(s);
        return NULL;
    }

    return n;
}

/**
 * @private
 */
INLINE const char *_sa_ipv6_get_scope(struct sockaddr_in6 *sa) {
    if (sa == NULL) return NULL;

    return sa_scope_get_name(sa->sin6_scope_id);
}

/**
 * @brief Gets the scope of a socket address.
 * @attention Caller should use sa_free(s) to clean up.
 * @param sa Pointer to a socket address.
 * @return -1 on failure, otherwise a scope name.
 * @public
 */
const char *sa_get_scope(struct sockaddr *sa) {
    if (sa == NULL) return NULL;

    switch (sa->sa_family) {

        case AF_INET6:
            return _sa_ipv6_get_scope((struct sockaddr_in6 *) sa);

    }

    return NULL;
}

/**
 * @brief Finds the index for the name of a scope (network interface).
 * @param scope The name of a scope (network interface).
 * @return The index of the scope (network interface).
 * @public
 */
uint16_t sa_scope_get_index(const char *scope) {
    if (scope == NULL) return 0;

    return if_nametoindex(scope);
}

/**
 * @private
 */

INLINE SA_BOOL _sa_set_ipv6_scope(struct sockaddr_in6 *sa, const char *scope) {
    sa->sin6_scope_id = sa_scope_get_index(scope);
    return 1;
}

/**
 * @brief Sets the scope (network interface) name of a socket address.
 * @param sa Pointer to a socket address.
 * @param scope The name of a scope (network interface).
 * @return Non-zero on success.
 * @public
 */
SA_BOOL sa_set_scope(struct sockaddr *sa, const char *scope) {
    if (sa == NULL) return 0;

    switch (sa->sa_family) {

        case AF_INET6:
            return _sa_set_ipv6_scope((struct sockaddr_in6 *) sa, scope);

    }

    return 0;
}

/**
 * @private
 */
INLINE uint32_t _sa_ipv6_get_scope_index(struct sockaddr_in6 *sa) {
    return sa->sin6_scope_id;
}

/**
 * @brief Gets the scope (network interface) index of a socket address.
 * @param sa Pointer to a socket address.
 * @return Zero on failure or no scope, otherwise a valid scope index.
 * @public
 */
uint32_t sa_get_scope_index(struct sockaddr *sa) {
    if (sa == NULL) return 0;

    switch (sa->sa_family) {

        case AF_INET6:
            return _sa_ipv6_get_scope_index((struct sockaddr_in6 *) sa);

    }

    return 0;
}

/**
 * @private
 */
INLINE SA_BOOL _sa_set_ipv6_scope_index(struct sockaddr_in6 *sa, uint32_t scope) {
    sa->sin6_scope_id = scope;
    return 1;
}

/**
 * @brief Sets the scope (network interface) index of a socket address.
 * @param sa Pointer to a socket address.
 * @param scope The index of a scope (network interface).
 * @return Non-zero on success.
 * @public
 */
SA_BOOL sa_set_scope_index(struct sockaddr *sa, uint32_t scope) {
    if (sa == NULL) return 0;

    switch (sa->sa_family) {

        case AF_INET6:
            return _sa_set_ipv6_scope_index((struct sockaddr_in6 *) sa, scope);

    }

    return 0;
}