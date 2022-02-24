#include "common.h"
#include "sa.h"
#include "sa_mm.h"

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
