#include <gtest/gtest.h>
#include "../common.h"
#include "../sa.h"

TEST(sa, has_len_field) {
#ifdef HAVE_SOCKADDR_SA_LEN
    EXPECT_EQ(sa_has_len_field(), true);
#else
    EXPECT_EQ(sa_has_len_field(), offsetof(struct sockaddr, sa_family) != 0);
#endif
}

