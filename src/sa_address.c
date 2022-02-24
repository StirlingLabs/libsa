#include "common.h"
#include "sa.h"

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
