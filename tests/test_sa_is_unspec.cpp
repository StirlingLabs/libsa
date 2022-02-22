#include <gtest/gtest.h>
#include "../common.h"
#include "../sa.h"

TEST(sa, is_unspec_true) {
    sockaddr_in6 sa;
    sa.sin6_family = AF_UNSPEC;
    sa.sin6_port = htons(1000);

    auto actual = sa_is_unspec(reinterpret_cast<sockaddr *>(&sa));

    EXPECT_EQ(actual, true);
}

TEST(sa, is_unspec_false) {
    sockaddr_in sa;
    sa.sin_family = AF_INET;
    sa.sin_port = htons(1000);

    EXPECT_EQ(inet_pton(AF_INET, "1.2.3.4", &sa.sin_addr), 1);

    auto actual = sa_is_unspec(reinterpret_cast<sockaddr *>(&sa));

    EXPECT_EQ(actual, false);
}