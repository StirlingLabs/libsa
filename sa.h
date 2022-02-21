#pragma once

#ifdef __cplusplus

#include <cstdint>

#else

#include <stdint.h>
#include <stdalign.h>
#include <assert.h>

#endif

#if _WIN32
#define SA_EXPORT __declspec(dllexport) extern
#else
#define SA_EXPORT extern
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define SA_BOOL int


/**
 * A memory allocation function that can be used by this implementation.
 * @param size A size in bytes to allocate.
 */
typedef void *sa_alloc_t(size_t size);

/**
 * A memory freeing function that can be used by this implementation.
 * @param p A pointer to memory to be freed.
 */
typedef void sa_free_t(const void *p);

#define sa_mm_fns_align sizeof(void*)*2

/**
 * A matched pair of memory allocation and free functions.
 */
typedef struct sa_mm_fns {
    alignas(sa_mm_fns_align) sa_alloc_t * alloc;
    sa_free_t * free;
} sa_mm_fns_t;

static_assert(sizeof(sa_mm_fns_t) == sa_mm_fns_align,
        "must be exactly the size of 2 pointers");

static_assert(alignof(sa_mm_fns_t) == sa_mm_fns_align,
        "must be exactly the alignment of 2 pointers");

/**
 * Identifies socket addresses that are AF_UNSPEC.
 * @param sa Pointer to a socket address.
 * @return non-zero if the @param sa is AF_UNSPEC.
 */
SA_EXPORT SA_BOOL sa_is_unspec(struct sockaddr *sa);

/**
 * Identifies socket addresses that are AF_INET.
 * @param sa Pointer to a socket address.
 * @return non-zero if the @param sa is AF_INET.
 */
SA_EXPORT SA_BOOL sa_is_ipv4(struct sockaddr *sa);

/**
 * Identifies socket addresses that are AF_INET6.
 * @param sa Pointer to a socket address.
 * @return non-zero if the @param sa is AF_INET6.
 */
SA_EXPORT SA_BOOL sa_is_ipv6(struct sockaddr *sa);

/**
 * Gets the copyable size of the socket address.
 * @param sa Pointer to a socket address.
 * @return Zero if unknown, otherwise the relevant copyable size.
 */
SA_EXPORT size_t sa_get_size(struct sockaddr *sa);

/**
 * Gets the copyable size of a socket address of a given family.
 * @attention This is provided for advanced use at the user's discretion.
 * @param family A platform specific address family.
 * @return The size of a sockaddr_storage structure if unknown, otherwise the relevant copyable size.
 */
SA_EXPORT size_t sa_get_size_by_family(uint16_t family);

/**
 * Gets the copyable size of a sockaddr_storage structure.
 * @attention The return value may be treated as constant.
 * @return The copyable size.
 */
SA_EXPORT size_t sa_get_size_storage();

/**
 * Gets a generally safe copyable size of an unspecified family sockaddr structure.
 * @attention The return value may be treated as constant.
 * @return The copyable size.
 */
SA_EXPORT size_t sa_get_size_unspec();

/**
 * Gets the copyable size of a sockaddr_in structure.
 * @attention The return value may be treated as constant.
 * @return The copyable size.
 */
SA_EXPORT size_t sa_get_size_ipv4();

/**
 * Gets the copyable size of a sockaddr_in6 structure.
 * @attention The return value may be treated as constant.
 * @return The copyable size.
 */
SA_EXPORT size_t sa_get_size_ipv6();

/**
 * Converts the address within the socket address to a string.
 * @attention Caller should use sa_free(s) to clean up.
 * @param sa Pointer to a socket address.
 * @return NULL if not possible, otherwise a pointer to a string.
 */
SA_EXPORT const char *sa_address_to_str(struct sockaddr *sa);

/**
 * Creates an AF_UNSPEC socket address.
 * @attention Caller should use sa_free(sa) to clean up.
 * @param port A port number to use.
 * @return NULL on failure, otherwise a pointer to the created socket address.
 */
SA_EXPORT struct sockaddr *sa_unspec(uint16_t port);

/**
 * Creates an AF_INET socket address.
 * @attention Caller should use sa_free(sa) to clean up.
 * @param str A IPv4 string to parse.
 * @param port A port number to use.
 * @return NULL on failure, otherwise a pointer to the created socket address.
 */
SA_EXPORT struct sockaddr *sa_ipv4(const char *str, uint16_t port);

/**
 * Creates an AF_INET6 socket address.
 * @attention Caller should use sa_free(sa) to clean up.
 * @param str A IPv6 string to parse.
 * @param port A port number to use.
 * @return NULL on failure, otherwise a pointer to the created socket address.
 */
SA_EXPORT struct sockaddr *sa_ipv6(const char *str, uint16_t port);

/**
 * Gets the port of a socket address.
 * @param sa Pointer to a socket address.
 * @return -1 on failure, otherwise a port number.
 */
SA_EXPORT int sa_get_port(struct sockaddr *sa);

/**
 * Sets the port of a socket address.
 * @param sa Pointer to a socket address.
 * @param port A port number to use.
 * @return Non-zero on success.
 */
SA_EXPORT SA_BOOL sa_set_port(struct sockaddr *sa, uint16_t port);

/**
 * Gets the scope of a socket address.
 * @attention Caller should use sa_free(s) to clean up.
 * @param sa Pointer to a socket address.
 * @return -1 on failure, otherwise a scope name.
 */
SA_EXPORT const char *sa_get_scope(struct sockaddr *sa);

/**
 * Sets the scope (network interface) name of a socket address.
 * @param sa Pointer to a socket address.
 * @param scope The name of a scope (network interface).
 * @return Non-zero on success.
 */
SA_EXPORT SA_BOOL sa_set_scope(struct sockaddr *sa, const char *scope);

/**
 * Gets the scope (network interface) index of a socket address.
 * @param sa Pointer to a socket address.
 * @return Zero on failure or no scope, otherwise a valid scope index.
 */
SA_EXPORT uint32_t sa_get_scope_index(struct sockaddr *sa);

/**
 * Sets the scope (network interface) index of a socket address.
 * @param sa Pointer to a socket address.
 * @param scope The index of a scope (network interface).
 * @return Non-zero on success.
 */
SA_EXPORT SA_BOOL sa_set_scope_index(struct sockaddr *sa, uint32_t scope);

/**
 * Sets the platform specific address family of a socket address.
 * @attention This is provided for advanced use at the user's discretion.
 * @param sa Pointer to a socket address.
 * @param family A platform specific address family value to specify.
 * @return Non-zero on success.
 */
SA_EXPORT SA_BOOL sa_set_family(struct sockaddr *sa, int family);

/**
 * Gets the platform specific address family of a socket address.
 * @attention This is provided for advanced use at the user's discretion.
 * @param sa Pointer to a socket address.
 * @return -1 on failure, otherwise the platform specific address family value.
 */
SA_EXPORT int sa_get_family(const struct sockaddr *sa);

/**
 * Detects if the socket address structure has a length field.
 * @attention This is provided for advanced use at the user's discretion.
 * @return Non-zero when true.
 */
SA_EXPORT SA_BOOL sa_has_len_field(void);

/**
 * Detects the address family field offset.
 * @attention This is provided for advanced use at the user's discretion.
 * @return The offset of the address family field in the socket address structure.
 */
SA_EXPORT ptrdiff_t sa_family_offset(void);

/**
 * Frees anything allocated by this library.
 * @param p A pointer to something allocated by this library.
 */
SA_EXPORT void sa_free(const void *p);

/**
 * Gets a byte from the address part of the socket address structure.
 * @param sa Pointer to a socket address.
 * @param offset An offset into the address.
 * @return -1 on failure, otherwise the value of the read byte.
 */
SA_EXPORT int sa_get_address_byte(struct sockaddr *sa, size_t offset);

/**
 * Sets a byte within the address part of the socket address structure.
 * @param sa Pointer to a socket address.
 * @param offset An offset into the address.
 * @param value The byte value to write.
 * @return Non-zero on success.
 */
SA_EXPORT SA_BOOL sa_set_address_byte(struct sockaddr *sa, size_t offset, uint8_t value);

/**
 * Gets the name of a scope (network interface) index.
 * @param scope The index of a scope (network interface).
 * @return The name of the scope (network interface).
 */
SA_EXPORT const char *sa_scope_get_name(uint16_t scope);

/**
 * Finds the index for the name of a scope (network interface).
 * @param scope The name of a scope (network interface).
 * @return The index of the scope (network interface).
 */
SA_EXPORT uint16_t sa_scope_get_index(const char *scope);

/**
 * Gets the previous and sets the new memory management functions,
 * or if the parameter is NULL, gets the current memory management functions.
 * @param p Null or a pointer to the new memory management functions.
 * @return The previous or current memory management functions.
 */
SA_EXPORT sa_mm_fns_t xch_sa_mm_fns(sa_mm_fns_t *p);


#ifdef __cplusplus
}
#endif

#undef SA_EXPORT

