#include <gtest/gtest.h>
#include "common.h"
#include "sa.h"

TEST(sa, ipv6) {
    const char *s = "::ffff:0102:0304";

    sockaddr_in6 expected;
    expected.sin6_family = AF_INET6;
    expected.sin6_port = htons(1000);

    EXPECT_EQ(inet_pton(AF_INET6, s, &expected.sin6_addr), 1);

    auto actual = reinterpret_cast<sockaddr_in6 *>( sa_ipv6(s, 1000));

    EXPECT_NE(actual, nullptr);

    EXPECT_EQ(actual->sin6_family, expected.sin6_family);

    for (int i = 0; i < 16; ++i)
        EXPECT_EQ(reinterpret_cast<uint8_t *>(&actual->sin6_addr)[i],
                reinterpret_cast<uint8_t *>(&expected.sin6_addr)[i])
                            << "IPv6 differs at offset " << i;

    EXPECT_EQ(actual->sin6_port, expected.sin6_port);

    sa_free(actual);
}

TEST(sa, ipv6_bin) {
    const char *s = "::ffff:0102:0304";

    sockaddr_in6 expected;
    expected.sin6_family = AF_INET6;
    expected.sin6_port = htons(1000);

    EXPECT_EQ(inet_pton(AF_INET6, s, &expected.sin6_addr), 1);

    auto actual = reinterpret_cast<sockaddr_in6 *>( sa_ipv6_bin((const uint8_t *)&expected.sin6_addr, 1000));

    EXPECT_NE(actual, nullptr);

    EXPECT_EQ(actual->sin6_family, expected.sin6_family);

    for (int i = 0; i < 16; ++i)
        EXPECT_EQ(reinterpret_cast<uint8_t *>(&actual->sin6_addr)[i],
                reinterpret_cast<uint8_t *>(&expected.sin6_addr)[i])
                            << "IPv6 differs at offset " << i;

    EXPECT_EQ(actual->sin6_port, expected.sin6_port);

    sa_free(actual);
}