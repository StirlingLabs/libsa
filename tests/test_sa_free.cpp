#include <gtest/gtest.h>
#include "../common.h"
#include "../sa.h"

bool sa_free_wrap_called;
sa_mm_fns_t old_mm;
sa_mm_fns_t new_mm;
void sa_free_wrap(const void * p) {
    sa_free_wrap_called = true;
    old_mm.free(p);
}

TEST(sa, free_1) {

    auto sa = sa_ipv4("1.2.3.4", 1000);

    auto s = sa_address_to_str(sa);

    sa_free_wrap_called = false;
    
    old_mm = xch_sa_mm_fns(nullptr);

    new_mm = old_mm;
    new_mm.free = sa_free_wrap;

    xch_sa_mm_fns(&new_mm);

    sa_free(sa);

    EXPECT_TRUE(sa_free_wrap_called);

    sa_free_wrap_called = false;

    sa_free(s);

    EXPECT_TRUE(sa_free_wrap_called);
    
    xch_sa_mm_fns(&old_mm);
}

TEST(sa, free_2) {

    auto sa = sa_ipv6("::1", 1000);

    auto s = sa_address_to_str(sa);

    sa_free_wrap_called = false;

    old_mm = xch_sa_mm_fns(nullptr);

    new_mm = old_mm;
    new_mm.free = sa_free_wrap;

    xch_sa_mm_fns(&new_mm);

    sa_free(sa);

    EXPECT_TRUE(sa_free_wrap_called);

    sa_free_wrap_called = false;

    sa_free(s);

    EXPECT_TRUE(sa_free_wrap_called);

    xch_sa_mm_fns(&old_mm);
}

TEST(sa, free_3) {

    auto sa = sa_unspec(1000);

    auto s = sa_address_to_str(sa);

    sa_free_wrap_called = false;

    old_mm = xch_sa_mm_fns(nullptr);

    new_mm = old_mm;
    new_mm.free = sa_free_wrap;

    xch_sa_mm_fns(&new_mm);

    sa_free(sa);

    EXPECT_TRUE(sa_free_wrap_called);

    sa_free_wrap_called = false;

    sa_free(s);

    EXPECT_TRUE(sa_free_wrap_called);

    xch_sa_mm_fns(&old_mm);
}



