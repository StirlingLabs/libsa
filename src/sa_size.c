#include "common.h"
#include "sa.h"

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
