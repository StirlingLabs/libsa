#pragma once

#include <cstdint>

#if _WIN32
#define SOCKADDR_NET_EXPORT __declspec(dllexport) extern
#else
#define SOCKADDR_NET_EXPORT extern
#endif

#ifdef __cplusplus
extern "C" {
#endif

SOCKADDR_NET_EXPORT bool sa_is_ipv4(struct sockaddr *sa);

SOCKADDR_NET_EXPORT bool sa_is_ipv6(struct sockaddr *sa);

SOCKADDR_NET_EXPORT const char *sa_ipv4_to_str(struct sockaddr *sa);

SOCKADDR_NET_EXPORT const char *sa_ipv6_to_str(struct sockaddr *sa);

SOCKADDR_NET_EXPORT const char *sa_to_str(struct sockaddr *sa);

SOCKADDR_NET_EXPORT struct sockaddr *sa_ipv4(const char *str, uint16_t port);

SOCKADDR_NET_EXPORT struct sockaddr *sa_ipv6(const char *str, uint16_t port);

SOCKADDR_NET_EXPORT int sa_get_port(struct sockaddr *sa);

SOCKADDR_NET_EXPORT bool sa_set_port(struct sockaddr *sa, uint16_t port);

SOCKADDR_NET_EXPORT const char * sa_get_scope(struct sockaddr *sa);

SOCKADDR_NET_EXPORT bool sa_set_scope(struct sockaddr *sa, const char * scope);

#ifdef __cplusplus
}
#endif
