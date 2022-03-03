#include "common.h"
#include "sa.h"

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

int sa_get_family_unspec() {
    return AF_UNSPEC;
}

int sa_get_family_ipv4() {
    return AF_INET;
}

int sa_get_family_ipv6() {
    return AF_INET6;
}