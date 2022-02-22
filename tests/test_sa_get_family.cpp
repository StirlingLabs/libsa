#include <gtest/gtest.h>
#include "../common.h"
#include "../sa.h"

TEST(sa, get_family_unspec) {
    sockaddr_in sa;
    sa.sin_family = AF_UNSPEC;
    sa.sin_port = htons(1000);

    auto actual = sa_get_family(reinterpret_cast<sockaddr *>(&sa));

    EXPECT_EQ(actual, AF_UNSPEC);
}

TEST(sa, get_family_ipv4) {
    sockaddr_in sa;
    sa.sin_family = AF_INET;
    sa.sin_port = htons(1000);

    EXPECT_EQ(inet_pton(AF_INET, "1.2.3.4", &sa.sin_addr), 1);

    auto actual = sa_get_family(reinterpret_cast<sockaddr *>(&sa));

    EXPECT_EQ(actual, AF_INET);
}

TEST(sa, get_family_ipv6) {
    sockaddr_in6 sa;
    sa.sin6_family = AF_INET6;
    sa.sin6_port = htons(1000);

    EXPECT_EQ(inet_pton(AF_INET6, "::ffff:0102:0304", &sa.sin6_addr), 1);

    auto actual = sa_get_family(reinterpret_cast<sockaddr *>(&sa));

    EXPECT_EQ(actual, AF_INET6);
}