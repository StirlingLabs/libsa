/*! @file
 * @brief The libsa API header.
 */

 #pragma once

#ifdef __cplusplus

#include <cstdint>

#else

#include <stdint.h>
#include <stdalign.h>
#include <assert.h>

#endif

/*!
 * @brief SA_BOOL booleans are non-zero integers for true, zero for false.
 * */
#ifdef DOXYGEN
#define SA_EXPORT extern
#else
#if _WIN32
#define SA_EXPORT __declspec(dllexport) extern
#else
#define SA_EXPORT __attribute__((visibility("default"))) extern
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief SA_BOOL booleans are non-zero integers for true, zero for false.
 * */
#define SA_BOOL int

/*!
 * @brief A memory allocation function that can be used by this implementation.
 * @param[in] size A size in bytes to allocate.
 * */
typedef void *sa_alloc_t(size_t size);

/*!
 * @brief A memory freeing function that can be used by this implementation.
 * @param[in] p A pointer to memory to be freed.
 * */
typedef void sa_free_t(const void *p);

/*!
 * The alignment of the memory management functions structure.
 */
#define sa_mm_fns_align (sizeof(void*)*2)

/*!
 * @brief A matched pair of memory allocation and free functions.
 * */
typedef struct sa_mm_fns {
    alignas(sa_mm_fns_align) sa_alloc_t * alloc;
    sa_free_t * free;
} sa_mm_fns_t;

static_assert(sizeof(sa_mm_fns_t) == sa_mm_fns_align,
        "must be exactly the size of 2 pointers");

static_assert(alignof(sa_mm_fns_t) == sa_mm_fns_align,
        "must be exactly the alignment of 2 pointers");

/*!
 * @brief Identifies socket addresses that are AF_UNSPEC.
 * @param[in] sa Pointer to a socket address.
 * @return non-zero if the sa is AF_UNSPEC.
 * */
SA_EXPORT SA_BOOL sa_is_unspec(struct sockaddr *sa);

/*!
 * @brief Identifies socket addresses that are AF_INET.
 * @param[in] sa Pointer to a socket address.
 * @return non-zero if the sa is AF_INET.
 * */
SA_EXPORT SA_BOOL sa_is_ipv4(struct sockaddr *sa);

/*!
 * @brief Identifies socket addresses that are AF_INET6.
 * @param[in] sa Pointer to a socket address.
 * @return non-zero if the sa is AF_INET6.
 * */
SA_EXPORT SA_BOOL sa_is_ipv6(struct sockaddr *sa);

/*!
 * @brief Gets the copyable size of the socket address.
 * @param[in] sa Pointer to a socket address.
 * @return Zero if unknown, otherwise the relevant copyable size.
 * */
SA_EXPORT size_t sa_get_size(struct sockaddr *sa);

/*!
 * @brief Gets the copyable size of a socket address of a given family.
 * @attention This is provided for advanced use at the user's discretion.
 * @param[in] family A platform specific address family.
 * @return The size of a sockaddr_storage structure if unknown, otherwise the relevant copyable size.
 * */
SA_EXPORT size_t sa_get_size_by_family(uint16_t family);

/*!
 * @brief Gets the copyable size of a sockaddr_storage structure.
 * @attention The return value may be treated as constant.
 * @return The copyable size.
 * */
SA_EXPORT size_t sa_get_size_storage();

/*!
 * @brief Gets a generally safe copyable size of an unspecified family sockaddr structure.
 * @attention The return value may be treated as constant.
 * @return The copyable size.
 * */
SA_EXPORT size_t sa_get_size_unspec();

/*!
 * @brief Gets the copyable size of a sockaddr_in structure.
 * @attention The return value may be treated as constant.
 * @return The copyable size.
 * */
SA_EXPORT size_t sa_get_size_ipv4();

/*!
 * @brief Gets the copyable size of a sockaddr_in6 structure.
 * @attention The return value may be treated as constant.
 * @return The copyable size.
 * */
SA_EXPORT size_t sa_get_size_ipv6();

/*!
 * @brief Converts the address within the socket address to a string.
 * @attention Caller should use sa_free(s) to clean up.
 * @param[in] sa Pointer to a socket address.
 * @return NULL if not possible, otherwise a pointer to a string.
 * */
SA_EXPORT const char *sa_address_to_str(struct sockaddr *sa);

/*!
 * @brief Creates an AF_UNSPEC socket address.
 * @attention Caller should use sa_free(sa) to clean up.
 * @param[in] port A port number to use.
 * @return NULL on failure, otherwise a pointer to the created socket address.
 * */
SA_EXPORT struct sockaddr *sa_unspec(uint16_t port);


/*!
 * @brief Creates an AF_INET socket address.
 * @attention Caller should use sa_free(sa) to clean up.
 * @param[in] str A IPv4 string to parse.
 * @param[in] port A port number to use.
 * @return NULL on failure, otherwise a pointer to the created socket address.
 * */
SA_EXPORT struct sockaddr *sa_ipv4(const char *str, uint16_t port);

/*!
 * @brief Creates an AF_INET socket address.
 * @attention Caller should use sa_free(sa) to clean up.
 * @param[in] address A IPv4 address in network byte order.
 * @param[in] port A port number to use.
 * @return NULL on failure, otherwise a pointer to the created socket address.
 * */
SA_EXPORT struct sockaddr *sa_ipv4_bin(const uint8_t *address, uint16_t port);

/*!
 * @brief Creates an AF_INET6 socket address.
 * @attention Caller should use sa_free(sa) to clean up.
 * @param[in] str A IPv6 string to parse.
 * @param[in] port A port number to use.
 * @return NULL on failure, otherwise a pointer to the created socket address.
 * */
SA_EXPORT struct sockaddr *sa_ipv6(const char *str, uint16_t port);

/*!
 * @brief Creates an AF_INET6 socket address.
 * @attention Caller should use sa_free(sa) to clean up.
 * @param[in] address A IPv6 address in network byte order.
 * @param[in] port A port number to use.
 * @return NULL on failure, otherwise a pointer to the created socket address.
 * */
SA_EXPORT struct sockaddr *sa_ipv6_bin(const uint8_t *address, uint16_t port);

/*!
 * @brief Gets the port of a socket address.
 * @param[in] sa Pointer to a socket address.
 * @return -1 on failure, otherwise a port number.
 * */
SA_EXPORT int sa_get_port(struct sockaddr *sa);

/*!
 * @brief Sets the port of a socket address.
 * @param[in] sa Pointer to a socket address.
 * @param[in] port A port number to use.
 * @return Non-zero on success.
 * */
SA_EXPORT SA_BOOL sa_set_port(struct sockaddr *sa, uint16_t port);

/*!
 * @brief Gets the scope of a socket address.
 * @attention Caller should use sa_free(s) to clean up.
 * @param[in] sa Pointer to a socket address.
 * @return -1 on failure, otherwise a scope name.
 * */
SA_EXPORT const char *sa_get_scope(struct sockaddr *sa);

/*!
 * @brief Sets the scope (network interface) name of a socket address.
 * @param[in] sa Pointer to a socket address.
 * @param[in] scope The name of a scope (network interface).
 * @return Non-zero on success.
 * */
SA_EXPORT SA_BOOL sa_set_scope(struct sockaddr *sa, const char *scope);

/*!
 * @brief Gets the scope (network interface) index of a socket address.
 * @param[in] sa Pointer to a socket address.
 * @return Zero on failure or no scope, otherwise a valid scope index.
 * */
SA_EXPORT uint32_t sa_get_scope_index(struct sockaddr *sa);

/*!
 * @brief Sets the scope (network interface) index of a socket address.
 * @param[in] sa Pointer to a socket address.
 * @param[in] scope The index of a scope (network interface).
 * @return Non-zero on success.
 * */
SA_EXPORT SA_BOOL sa_set_scope_index(struct sockaddr *sa, uint32_t scope);

/*!
 * @brief Sets the platform specific address family of a socket address.
 * @attention This is provided for advanced use at the user's discretion.
 * @param[in] sa Pointer to a socket address.
 * @param[in] family A platform specific address family value to specify.
 * @return Non-zero on success.
 * */
SA_EXPORT SA_BOOL sa_set_family(struct sockaddr *sa, int family);

/*!
 * @brief Gets the platform specific address family of a socket address.
 * @attention This is provided for advanced use at the user's discretion.
 * @param[in] sa Pointer to a socket address.
 * @return -1 on failure, otherwise the platform specific address family value.
 * */
SA_EXPORT int sa_get_family(const struct sockaddr *sa);

/*!
 * @brief Gets the platform specific address family of an unspecified (AF_UNSPEC) socket address.
 * @attention This is provided for advanced use at the user's discretion.
 * @return -1 on failure, otherwise the platform specific address family value.
 * */
SA_EXPORT int sa_get_family_unspec();

/*!
 * @brief Gets the platform specific address family of an IPv4 (AF_INET) socket address.
 * @attention This is provided for advanced use at the user's discretion.
 * @return -1 on failure, otherwise the platform specific address family value.
 * */
SA_EXPORT int sa_get_family_ipv4();

/*!
 * @brief Gets the platform specific address family of an IPv6 (AF_INET6) socket address.
 * @attention This is provided for advanced use at the user's discretion.
 * @return -1 on failure, otherwise the platform specific address family value.
 * */
SA_EXPORT int sa_get_family_ipv6();

/*!
 * @brief Detects if the socket address structure has a length field.
 * @attention This is provided for advanced use at the user's discretion.
 * @return Non-zero when true.
 * */
SA_EXPORT SA_BOOL sa_has_len_field(void);

/*!
 * @brief Detects the address family field offset.
 * @attention This is provided for advanced use at the user's discretion.
 * @return The offset of the address family field in the socket address structure.
 * */
SA_EXPORT ptrdiff_t sa_family_offset(void);

/*!
 * @brief Frees anything allocated by this library.
 * @param[in] p A pointer to something allocated by this library.
 * */
SA_EXPORT void sa_free(const void *p);

/*!
 * @brief Gets a byte from the address part of the socket address structure.
 * @param[in] sa Pointer to a socket address.
 * @param[in] offset An offset into the address.
 * @return -1 on failure, otherwise the value of the read byte.
 * */
SA_EXPORT int sa_get_address_byte(struct sockaddr *sa, size_t offset);

/*!
 * @brief Sets a byte within the address part of the socket address structure.
 * @param[in] sa Pointer to a socket address.
 * @param[in] offset An offset into the address.
 * @param[in] value The byte value to write.
 * @return Non-zero on success.
 * */
SA_EXPORT SA_BOOL sa_set_address_byte(struct sockaddr *sa, size_t offset, uint8_t value);

/*!
 * @brief Allows direct memory access to the address bytes of a socket address. 
 * @param[in] sa Pointer to a socket address.
 * @param[in] size Reports the count of bytes that make up the memory region.
 * @return Null on failure, otherwise a pointer to the address bytes of a socket address.
 * */
SA_EXPORT const uint8_t* sa_address_bytes(struct sockaddr *sa, size_t* size);


/*!
 * @brief Gets the name of a scope (network interface) index.
 * @param[in] scope The index of a scope (network interface).
 * @return The name of the scope (network interface).
 * */
SA_EXPORT const char *sa_scope_get_name(uint16_t scope);

/*!
 * @brief Finds the index for the name of a scope (network interface).
 * @param[in] scope The name of a scope (network interface).
 * @return The index of the scope (network interface).
 * */
SA_EXPORT uint16_t sa_scope_get_index(const char *scope);

/*!
 * @brief Gets or sets the memory management functions.
 *
 * Gets the previous and sets the new memory management functions,
 * or if the parameter is NULL, gets the current memory management functions.
 * @param[in] p Null or a pointer to the new memory management functions.
 * @return The previous or current memory management functions.
 * */
SA_EXPORT sa_mm_fns_t xch_sa_mm_fns(sa_mm_fns_t *p);

#ifdef __cplusplus
}
#endif

#undef SA_EXPORT

