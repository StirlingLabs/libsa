#include <gtest/gtest.h>
#include "../common.h"
#include "../sa.h"

TEST(libsatest, test_sa_ipv6_to_str) {
    const char *s = "::ffff:0102:0304";
    const char *expected = "::ffff:1.2.3.4";

    sockaddr_in6 sa{.sin6_family = AF_INET6, .sin6_port = htons(1000)};

    EXPECT_EQ(inet_pton(AF_INET6, s, &sa.sin6_addr), 1);

    auto actual = sa_ipv6_to_str(reinterpret_cast<sockaddr *>(&sa));

    EXPECT_NE(actual, nullptr);

    EXPECT_STREQ(actual, expected);

    delete actual;
}