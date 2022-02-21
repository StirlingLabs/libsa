#include "common.h"
#include "sa.h"

static void *default_sa_alloc(size_t size) {
    void *p = malloc(size);
    memset(p, 0, size);
    return p;
}

static void default_free(const void *ptr) {
    free((void *) ptr);
}

alignas(sa_mm_fns_align)
static sa_mm_fns_t sa_mm_fns = {default_sa_alloc, default_free};

sa_mm_fns_t xch_sa_mm_fns(sa_mm_fns_t *p) {
    // TODO: stdatomic.h; intrinsics? cmpxchg8/16b? see cas.h

    if (p == NULL || p->alloc == NULL || p->free == NULL) {
        return sa_mm_fns;
    }
    sa_mm_fns_t old = sa_mm_fns;
    sa_mm_fns = *p;
    return old;
}

INLINE void *sa_alloc(size_t size) {
    return (*sa_mm_fns.alloc)(size);
}

void sa_free(const void *p) {
    if (p != NULL) {
        (*sa_mm_fns.free)(p);
    }
}

SA_BOOL sa_is_unspec(struct sockaddr *sa) {
    if (sa == NULL) return 0;
    return sa->sa_family == AF_UNSPEC;
}

SA_BOOL sa_is_ipv4(struct sockaddr *sa) {
    if (sa == NULL) return 0;
    return sa->sa_family == AF_INET;
}

SA_BOOL sa_is_ipv6(struct sockaddr *sa) {
    if (sa == NULL) return 0;
    return sa->sa_family == AF_INET6;
}

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

size_t sa_get_size_storage() {
    return sizeof(struct sockaddr_storage);
}

size_t sa_get_size_unspec() {
    return sizeof(struct sockaddr_in6);
}

size_t sa_get_size_ipv4() {
    return sizeof(struct sockaddr_in);
}

size_t sa_get_size_ipv6() {
    return sizeof(struct sockaddr_in6);
}

INLINE const char *_sa_ipv4_to_str(struct sockaddr_in *sa) {
    char *s = sa_alloc(INET_ADDRSTRLEN);
    if (s == NULL) return NULL;

    if (inet_ntop(AF_INET, &sa->sin_addr, s, INET_ADDRSTRLEN) == NULL) {
        sa_free(s);
        return NULL;
    }
    return s;
}


INLINE const char *_sa_ipv6_to_str(struct sockaddr_in6 *sa) {
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
            return strdup("*");

        case AF_INET:
            return _sa_ipv4_to_str((struct sockaddr_in *) sa);

        case AF_INET6:
            return _sa_ipv6_to_str((struct sockaddr_in6 *) sa);
    }

    return NULL;
}

struct sockaddr *sa_unspec(uint16_t port) {
    struct sockaddr_in6 *sa = sa_alloc(sizeof(struct sockaddr_in6));
    if (sa == NULL) return NULL;

    sa->sin6_family = AF_UNSPEC;
    sa->sin6_port = htons(port);
    return (struct sockaddr *) sa;
}

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

INLINE const char *_sa_ipv6_get_scope(struct sockaddr_in6 *sa) {
    if (sa == NULL) return NULL;

    return sa_scope_get_name(sa->sin6_scope_id);
}

const char *sa_get_scope(struct sockaddr *sa) {
    if (sa == NULL) return NULL;

    switch (sa->sa_family) {

        case AF_INET6:
            return _sa_ipv6_get_scope((struct sockaddr_in6 *) sa);

    }

    return NULL;
}

uint16_t sa_scope_get_index(const char *scope) {
    if (scope == NULL) return 0;

    return if_nametoindex(scope);
}

INLINE SA_BOOL _sa_set_ipv6_scope(struct sockaddr_in6 *sa, const char *scope) {
    sa->sin6_scope_id = sa_scope_get_index(scope);
    return 1;
}

SA_BOOL sa_set_scope(struct sockaddr *sa, const char *scope) {
    if (sa == NULL) return 0;

    switch (sa->sa_family) {

        case AF_INET6:
            return _sa_set_ipv6_scope((struct sockaddr_in6 *) sa, scope);

    }

    return 0;
}

INLINE uint32_t _sa_ipv6_get_scope_index(struct sockaddr_in6 *sa) {
    return sa->sin6_scope_id;
}

uint32_t sa_get_scope_index(struct sockaddr *sa) {
    if (sa == NULL) return 0;

    switch (sa->sa_family) {

        case AF_INET6:
            return _sa_ipv6_get_scope_index((struct sockaddr_in6 *) sa);

    }

    return 0;
}

INLINE SA_BOOL _sa_set_ipv6_scope_index(struct sockaddr_in6 *sa, uint32_t scope) {
    sa->sin6_scope_id = scope;
    return 1;
}

SA_BOOL sa_set_scope_index(struct sockaddr *sa, uint32_t scope) {
    if (sa == NULL) return 0;

    switch (sa->sa_family) {

        case AF_INET6:
            return _sa_set_ipv6_scope_index((struct sockaddr_in6 *) sa, scope);

    }

    return 0;
}

SA_BOOL sa_set_family(struct sockaddr *sa, int family) {
    if (sa == NULL) return 0;
    sa->sa_family = family;
    return 1;
}

int sa_get_family(const struct sockaddr *sa) {
    return sa->sa_family;
}

SA_BOOL sa_has_len_field(void) {
#if HAVE_SOCKADDR_SA_LEN
    return 1;
#else
    return offsetof(struct sockaddr, sa_family) != 0;
#endif
}

ptrdiff_t sa_family_offset(void) {
    return offsetof(struct sockaddr, sa_family);
}


int _sa_get_ipv4_byte(struct sockaddr_in *sa, size_t offset) {
    if (offset >= sizeof(struct in_addr)) return -1;
    return ((uint8_t *) &sa->sin_addr)[offset];
}

int _sa_get_ipv6_byte(struct sockaddr_in6 *sa, size_t offset) {
    if (offset >= sizeof(struct in6_addr)) return -1;
    return ((uint8_t *) &sa->sin6_addr)[offset];
}

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

SA_BOOL _sa_set_ipv4_byte(struct sockaddr_in *sa, size_t offset, uint8_t value) {
    if (offset >= sizeof(struct in_addr)) return 0;
    ((uint8_t *) &sa->sin_addr)[offset] = value;
    return 1;
}

SA_BOOL _sa_set_ipv6_byte(struct sockaddr_in6 *sa, size_t offset, uint8_t value) {
    if (offset >= sizeof(struct in6_addr)) return 0;
    ((uint8_t *) &sa->sin6_addr)[offset] = value;
    return 1;
}

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
