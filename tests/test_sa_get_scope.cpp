#include <gtest/gtest.h>
#include "../common.h"
#include "../sa.h"

TEST(sa, get_scope_ipv4) {
    sockaddr_in sa;
    sa.sin_family = AF_INET;
    sa.sin_port = htons(1000);

    EXPECT_EQ(inet_pton(AF_INET, "1.2.3.4", &sa.sin_addr), 1);

    auto actual = sa_get_scope(reinterpret_cast<sockaddr *>(&sa));

    EXPECT_EQ(actual, nullptr);

    auto index = sa_get_scope_index(reinterpret_cast<sockaddr *>(&sa));

    EXPECT_EQ(index, 0);
}

TEST(sa, get_scope_ipv6_empty) {
    sockaddr_in6 sa;
    sa.sin6_family = AF_INET6;
    sa.sin6_port = htons(1000);
    sa.sin6_scope_id = 0;

    EXPECT_EQ(inet_pton(AF_INET6, "::ffff:0102:0304", &sa.sin6_addr), 1);

    auto actual = sa_get_scope(reinterpret_cast<sockaddr *>(&sa));

    EXPECT_EQ(actual, nullptr);

    auto index = sa_get_scope_index(reinterpret_cast<sockaddr *>(&sa));

    EXPECT_EQ(index, 0);
}


TEST(sa, get_scope_ipv6_1) {
    sockaddr_in6 sa;
    sa.sin6_family = AF_INET6;
    sa.sin6_port = htons(1000);
    sa.sin6_scope_id = 1;

    EXPECT_EQ(inet_pton(AF_INET6, "::ffff:0102:0304", &sa.sin6_addr), 1);

    auto actual = sa_get_scope(reinterpret_cast<sockaddr *>(&sa));

    EXPECT_NE(actual, nullptr);

    auto index = sa_get_scope_index(reinterpret_cast<sockaddr *>(&sa));

    EXPECT_EQ(index, 1);
}
