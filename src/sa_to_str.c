#include "common.h"
#include "sa.h"
#include "sa_mm.h"

INLINE static const char *_sa_unspec_to_str() {
    char *s = sa_alloc(2);
    if (s == NULL) return NULL;
    s[0] = '*';
    return s;
}

INLINE static const char *_sa_ipv4_to_str(struct sockaddr_in *sa) {
    char *s = sa_alloc(INET_ADDRSTRLEN);
    if (s == NULL) return NULL;

    if (inet_ntop(AF_INET, &sa->sin_addr, s, INET_ADDRSTRLEN) == NULL) {
        sa_free(s);
        return NULL;
    }
    return s;
}


INLINE static const char *_sa_ipv6_to_str(struct sockaddr_in6 *sa) {
    char *s = sa_alloc(INET6_ADDRSTRLEN);
    if (s == NULL) return NULL;

    if (inet_ntop(AF_INET6, &sa->sin6_addr, s, INET6_ADDRSTRLEN) == NULL) {
        sa_free(s);
        return NULL;
    }
    return s;
}

const char *sa_address_to_str(struct sockaddr *sa) {
    if (sa == NULL) return NULL;

    switch (sa->sa_family) {
        case AF_UNSPEC:
            return _sa_unspec_to_str();

        case AF_INET:
            return _sa_ipv4_to_str((struct sockaddr_in *) sa);

        case AF_INET6:
            return _sa_ipv6_to_str((struct sockaddr_in6 *) sa);
    }

    return NULL;
}
