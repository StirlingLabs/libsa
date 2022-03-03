#include "common.h"
#include "sa.h"

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
