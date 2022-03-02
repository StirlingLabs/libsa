/**
 * @file
 * @brief The libsa API header.
 *
 * This header defines the interfaces of the libsa cross-platform socket addresses
 * implemented by Stirling Labs.
 * @public
 */

#pragma once

#ifdef __cplusplus

#include <cstdint>

#else

#include <stdint.h>
#include <stdalign.h>
#include <assert.h>

#endif

/**
 * @brief SA_BOOL booleans are non-zero integers for true, zero for false.
 * @public
 */

/**
 * @private
 */
#if _WIN32
#define SA_EXPORT __declspec(dllexport) extern
#else
#define SA_EXPORT __attribute__((visibility("default"))) extern
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief SA_BOOL booleans are non-zero integers for true, zero for false.
 * @public
 */
#define SA_BOOL int

/**
 * @brief A memory allocation function that can be used by this implementation.
 * @param size A size in bytes to allocate.
 * @public
 */
typedef void *sa_alloc_t(size_t size);

/**
 * @brief A memory freeing function that can be used by this implementation.
 * @param p A pointer to memory to be freed.
 * @public
 */
typedef void sa_free_t(const void *p);

/**
 * @private
 */
#define sa_mm_fns_align (sizeof(void*)*2)

/**
 * @brief A matched pair of memory allocation and free functions.
 * @public
 */
typedef struct sa_mm_fns {
    alignas(sa_mm_fns_align) sa_alloc_t * alloc;
    sa_free_t * free;
} sa_mm_fns_t;

/**
 * @private
 */
static_assert(sizeof(sa_mm_fns_t) == sa_mm_fns_align,
        "must be exactly the size of 2 pointers");

/**
 * @private
 */
static_assert(alignof(sa_mm_fns_t) == sa_mm_fns_align,
        "must be exactly the alignment of 2 pointers");

SA_EXPORT SA_BOOL sa_is_unspec(struct sockaddr *sa);

SA_EXPORT SA_BOOL sa_is_ipv4(struct sockaddr *sa);

SA_EXPORT SA_BOOL sa_is_ipv6(struct sockaddr *sa);

SA_EXPORT size_t sa_get_size(struct sockaddr *sa);

SA_EXPORT size_t sa_get_size_by_family(uint16_t family);

SA_EXPORT size_t sa_get_size_storage();

SA_EXPORT size_t sa_get_size_unspec();

SA_EXPORT size_t sa_get_size_ipv4();

SA_EXPORT size_t sa_get_size_ipv6();

SA_EXPORT const char *sa_address_to_str(struct sockaddr *sa);

SA_EXPORT struct sockaddr *sa_unspec(uint16_t port);

SA_EXPORT struct sockaddr *sa_ipv4(const char *str, uint16_t port);

SA_EXPORT struct sockaddr *sa_ipv4_bin(const uint8_t *address, uint16_t port);

SA_EXPORT struct sockaddr *sa_ipv6(const char *str, uint16_t port);

SA_EXPORT struct sockaddr *sa_ipv6_bin(const uint8_t *address, uint16_t port);

SA_EXPORT int sa_get_port(struct sockaddr *sa);

SA_EXPORT SA_BOOL sa_set_port(struct sockaddr *sa, uint16_t port);

SA_EXPORT const char *sa_get_scope(struct sockaddr *sa);

SA_EXPORT SA_BOOL sa_set_scope(struct sockaddr *sa, const char *scope);

SA_EXPORT uint32_t sa_get_scope_index(struct sockaddr *sa);

SA_EXPORT SA_BOOL sa_set_scope_index(struct sockaddr *sa, uint32_t scope);

SA_EXPORT SA_BOOL sa_set_family(struct sockaddr *sa, int family);

SA_EXPORT int sa_get_family(const struct sockaddr *sa);

SA_EXPORT int sa_get_family_unspec();

SA_EXPORT int sa_get_family_ipv4();

SA_EXPORT int sa_get_family_ipv6();

SA_EXPORT SA_BOOL sa_has_len_field(void);

SA_EXPORT ptrdiff_t sa_family_offset(void);

SA_EXPORT void sa_free(const void *p);

SA_EXPORT int sa_get_address_byte(struct sockaddr *sa, size_t offset);

SA_EXPORT SA_BOOL sa_set_address_byte(struct sockaddr *sa, size_t offset, uint8_t value);

SA_EXPORT const uint8_t* sa_address_bytes(struct sockaddr *sa, size_t* size);

SA_EXPORT const char *sa_scope_get_name(uint16_t scope);

SA_EXPORT uint16_t sa_scope_get_index(const char *scope);

SA_EXPORT sa_mm_fns_t xch_sa_mm_fns(sa_mm_fns_t *p);

#ifdef __cplusplus
}
#endif

#undef SA_EXPORT

