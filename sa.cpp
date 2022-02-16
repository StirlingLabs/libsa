#include "common.h"
#include "sa.h"

#if defined(_MSC_VER) && !__INTEL_COMPILER && _MSC_VER >= 1310
#define INLINE __forceinline
#elif __GNUC__ || __has_attribute(always_inline)
#define INLINE __attribute__((always_inline))
#else
#define INLINE inline
#endif

extern "C" {

bool sa_is_ipv4(sockaddr *sa) {
    return sa->sa_family == AF_INET;
}

bool sa_is_ipv6(sockaddr *sa) {
    return sa->sa_family == AF_INET6;
}

INLINE const char *_inet_ntop4(sockaddr_in *sa) {
    char *s = new char[INET_ADDRSTRLEN]();
    if (inet_ntop(AF_INET, &sa->sin_addr, s, INET_ADDRSTRLEN) == nullptr) {
        free(s);
        return nullptr;
    }
    return s;
}

const char *sa_ipv4_to_str(sockaddr *sa) {
    if (sa == nullptr) return nullptr;
    if (sa->sa_family != AF_INET) return nullptr;
    return _inet_ntop4(reinterpret_cast<sockaddr_in *>(sa));
}


INLINE const char *_inet_ntop6(sockaddr_in6 *sa) {
    char *s = new char[INET6_ADDRSTRLEN]();
    if (inet_ntop(AF_INET6, &sa->sin6_addr, s, INET6_ADDRSTRLEN) == nullptr) {
        free(s);
        return nullptr;
    }
    return s;
}

const char *sa_ipv6_to_str(sockaddr *sa) {
    if (sa == nullptr) return nullptr;
    if (sa->sa_family != AF_INET6) return nullptr;
    return _inet_ntop6(reinterpret_cast<sockaddr_in6 *>(sa));
}


const char *sa_to_str(sockaddr *sa) {
    if (sa == nullptr) return nullptr;

    switch (sa->sa_family) {
        case AF_INET:
            return _inet_ntop4(reinterpret_cast<sockaddr_in *>(sa));

        case AF_INET6:
            return _inet_ntop6(reinterpret_cast<sockaddr_in6 *>(sa));
    }

    return nullptr;
}

sockaddr *sa_ipv4(const char *str, uint16_t port) {
    sockaddr_in *sa = new sockaddr_in();
    if (inet_pton(AF_INET, str, &sa->sin_addr) != 1) {
        free(sa);
        return nullptr;
    }
    sa->sin_family = AF_INET;
    sa->sin_port = htons(port);
    return reinterpret_cast<sockaddr *>(sa);
}

sockaddr *sa_ipv6(const char *str, uint16_t port) {
    sockaddr_in6 *sa = new sockaddr_in6();
    if (inet_pton(AF_INET6, str, &sa->sin6_addr) != 1) {
        free(sa);
        return nullptr;
    }
    sa->sin6_family = AF_INET6;
    sa->sin6_port = htons(port);
    return reinterpret_cast<sockaddr *>(sa);
}

int inet_get_port4(sockaddr_in *sa) {
    if (sa == nullptr) return -1;
    return ntohs(sa->sin_port);
}

int inet_get_port6(sockaddr_in6 *sa) {
    if (sa == nullptr) return -1;
    return ntohs(sa->sin6_port);
}

int sa_get_port(sockaddr *sa) {
    if (sa == nullptr) return -1;
    switch (sa->sa_family) {

        case AF_INET:
            return inet_get_port4(reinterpret_cast<sockaddr_in *>(sa));

        case AF_INET6:
            return inet_get_port6(reinterpret_cast<sockaddr_in6 *>(sa));

    }

    return -1;
}

INLINE bool _inet_set_port4(sockaddr_in *sa, uint16_t port) {
    sa->sin_port = htons(port);
    return true;
}

INLINE bool _inet_set_port6(sockaddr_in6 *sa, uint16_t port) {
    sa->sin6_port = htons(port);
    return true;
}

bool sa_set_port(sockaddr *sa, uint16_t port) {
    if (sa == nullptr) return false;
    switch (sa->sa_family) {

        case AF_INET:
            return _inet_set_port4(reinterpret_cast<sockaddr_in *>(sa), port);

        case AF_INET6:
            return _inet_set_port6(reinterpret_cast<sockaddr_in6 *>(sa), port);

    }

    return false;
}


INLINE const char *_inet_get_scope6(sockaddr_in6 *sa) {
    char *s = new char[IF_NAMESIZE]();
    return if_indextoname(sa->sin6_scope_id, s);
}

const char *sa_get_scope(sockaddr *sa) {
    if (sa == nullptr) return nullptr;
    switch (sa->sa_family) {

        case AF_INET6:
            return _inet_get_scope6(reinterpret_cast<sockaddr_in6 *>(sa));

    }

    return nullptr;
}

INLINE bool _inet_set_scope6(sockaddr_in6 *sa, const char *scope) {
    sa->sin6_scope_id = if_nametoindex(scope);
    return true;
}

bool sa_set_scope(sockaddr *sa, const char *scope) {
    if (sa == nullptr) return false;
    if (scope == nullptr) return false;
    switch (sa->sa_family) {

        case AF_INET6:
            return _inet_set_scope6(reinterpret_cast<sockaddr_in6 *>(sa), scope);

    }

    return false;
}

}