#include <gtest/gtest.h>
#include "../common.h"
#include "../sa.h"

TEST(libsatest, test_sa_get_port_ipv4) {
    sockaddr_in sa{.sin_family = AF_INET, .sin_port = htons(1000)};

    EXPECT_EQ(inet_pton(AF_INET, "1.2.3.4", &sa.sin_addr), 1);

    auto actual = sa_get_port(reinterpret_cast<sockaddr *>(&sa));

    EXPECT_EQ(actual, 1000);
}

TEST(libsatest, test_sa_get_port_ipv6) {
    sockaddr_in6 sa{.sin6_family = AF_INET6, .sin6_port = htons(1000)};

    EXPECT_EQ(inet_pton(AF_INET6, "::ffff:0102:0304", &sa.sin6_addr), 1);

    auto actual = sa_get_port(reinterpret_cast<sockaddr *>(&sa));

    EXPECT_EQ(actual, 1000);
}