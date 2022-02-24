#include <gtest/gtest.h>
#include "common.h"
#include "sa.h"


TEST(sa, address_to_str_ipv4) {
    const char *expected = "1.2.3.4";

    sockaddr_in sa;
    sa.sin_family = AF_INET;
    sa.sin_port = htons(1000);
    EXPECT_EQ(inet_pton(AF_INET, expected, &sa.sin_addr), 1);

    auto actual = sa_address_to_str(reinterpret_cast<sockaddr *>(&sa));

    EXPECT_NE(actual, nullptr);

    EXPECT_STREQ(actual, expected);

    sa_free(actual);
}

TEST(sa, address_to_str_ipv6) {
    const char *s = "::ffff:0102:0304";
    const char *expected = "::ffff:1.2.3.4";

    sockaddr_in6 sa;
    sa.sin6_family = AF_INET6;
    sa.sin6_port = htons(1000);

    EXPECT_EQ(inet_pton(AF_INET6, s, &sa.sin6_addr), 1);

    auto actual = sa_address_to_str(reinterpret_cast<sockaddr *>(&sa));

    EXPECT_NE(actual, nullptr);

    EXPECT_STREQ(actual, expected);

    sa_free(actual);
}