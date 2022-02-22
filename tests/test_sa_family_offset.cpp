#include <gtest/gtest.h>
#include "../common.h"
#include "../sa.h"

TEST(sa, family_offset) {
    EXPECT_EQ(sa_family_offset(), offsetof(struct sockaddr, sa_family));
}