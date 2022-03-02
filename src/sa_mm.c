#include "common.h"
#include "sa.h"
#include "sa_mm.h"
#include "atomic.h"

/**
 * @file
 * @brief Socket address memory management. 
 */

/**
 * @private
 */
#if INTPTR_MAX == INT64_MAX
static intptr_t sa_alloc_cookie = 0x7259813133E9FAA6;
#elif INTPTR_MAX == INT32_MAX
static intptr_t sa_alloc_cookie = 0x33E9FAA6;
#else
#error Not yet implemented
#endif

/**
 * @private
 */
typedef struct sa_alloc_header {
    intptr_t cookie;
    sa_free_t *free;
} sa_alloc_header_t;

/**
 * @private
 */
alignas(sa_mm_fns_align)
static sa_mm_fns_t sa_mm_fns;

/**
 * @private
 */
INLINE
static bool cas_mm_fns(sa_mm_fns_t *comparand, sa_mm_fns_t *exchange) {
    return cas((intptr2_t *) &sa_mm_fns, (intptr2_t *) comparand, (intptr2_t *) exchange);
}

/**
 * @private
 */
INLINE
static sa_mm_fns_t _to_mm_fns_t(intptr2_t x) {
    return (struct sa_mm_fns) {(sa_alloc_t *) intptr2_sub(x, 0), (sa_free_t *) intptr2_sub(x, 1)};
}

/**
 * @private
 */
INLINE
static sa_mm_fns_t read_mm_fns() {
    return _to_mm_fns_t(cas_read((intptr2_t *) &sa_mm_fns));
}

static void *default_sa_alloc(size_t size) {
    // assume size will always be greater than sizeof(sa_alloc_header_t) 
    void *p = malloc(size);
    memset(&((sa_alloc_header_t *) p)[1], 0, size - sizeof(sa_alloc_header_t));
    return p;
}

/**
 * @private
 */
static void default_free(const void *ptr) {
    free((void *) ptr);
}

/**
 * @private
 */
alignas(sa_mm_fns_align)
static sa_mm_fns_t sa_mm_fns = {default_sa_alloc, default_free};

/**
 * @brief Gets or sets the memory management functions.
 *
 * Gets the previous and sets the new memory management functions,
 * or if the parameter is NULL, gets the current memory management functions.
 * @param p Null or a pointer to the new memory management functions.
 * @return The previous or current memory management functions.
 * @public
 */
sa_mm_fns_t xch_sa_mm_fns(sa_mm_fns_t *p) {
    if (p == NULL || p->alloc == NULL || p->free == NULL) {
        return sa_mm_fns;
    }
    sa_mm_fns_t old = sa_mm_fns;
    while (!cas_mm_fns(&old, p)) {
        //old = sa_mm_fns;
    }
    sa_mm_fns = *p;
    return old;
}

void *sa_alloc(size_t size) {
    if (size == 0) return NULL;
    sa_mm_fns_t mm = read_mm_fns();
    void *p = (*mm.alloc)(size + sizeof(sa_alloc_header_t));
    sa_alloc_header_t *h = p;
    h->cookie = sa_alloc_cookie;
    h->free = mm.free;
    void *d = &h[1];
    return d;
}

/**
 * @brief Frees anything allocated by this library.
 * @param p A pointer to something allocated by this library.
 * @public
 */
void sa_free(const void *p) {
    if (p == NULL)
        return;
    sa_alloc_header_t *ph = &((sa_alloc_header_t *) p)[-1];
    sa_alloc_header_t h = *ph; // local copy
    if (h.cookie != sa_alloc_cookie)
        return;
    h.free(ph);
}
