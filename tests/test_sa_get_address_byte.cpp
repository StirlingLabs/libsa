#include <gtest/gtest.h>
#include "../common.h"
#include "../sa.h"

TEST(sa, get_address_byte_ipv4) {
    sockaddr_in sa;
    sa.sin_family = AF_INET;
    sa.sin_port = htons(1000);

    EXPECT_EQ(inet_pton(AF_INET, "1.2.3.4", &sa.sin_addr), 1);

    auto actual = sa_get_address_byte(reinterpret_cast<sockaddr *>(&sa), 0);

    EXPECT_EQ(actual, 1);

    actual = sa_get_address_byte(reinterpret_cast<sockaddr *>(&sa), 1);

    EXPECT_EQ(actual, 2);

    actual = sa_get_address_byte(reinterpret_cast<sockaddr *>(&sa), 2);

    EXPECT_EQ(actual, 3);

    actual = sa_get_address_byte(reinterpret_cast<sockaddr *>(&sa), 3);

    EXPECT_EQ(actual, 4);

    actual = sa_get_address_byte(reinterpret_cast<sockaddr *>(&sa), 4);

    EXPECT_EQ(actual, -1);

    actual = sa_get_address_byte(reinterpret_cast<sockaddr *>(&sa), -1);

    EXPECT_EQ(actual, -1);
}

TEST(sa, get_address_byte_ipv6) {
    sockaddr_in6 sa;
    sa.sin6_family = AF_INET6;
    sa.sin6_port = htons(1000);

    EXPECT_EQ(inet_pton(AF_INET6, "::ffff:0102:0304", &sa.sin6_addr), 1);

    auto actual = sa_get_address_byte(reinterpret_cast<sockaddr *>(&sa), 0);

    EXPECT_EQ(actual, 0);

    actual = sa_get_address_byte(reinterpret_cast<sockaddr *>(&sa), 1);

    EXPECT_EQ(actual, 0);

    actual = sa_get_address_byte(reinterpret_cast<sockaddr *>(&sa), 2);

    EXPECT_EQ(actual, 0);

    actual = sa_get_address_byte(reinterpret_cast<sockaddr *>(&sa), 3);

    EXPECT_EQ(actual, 0);

    actual = sa_get_address_byte(reinterpret_cast<sockaddr *>(&sa), 4);

    EXPECT_EQ(actual, 0);

    actual = sa_get_address_byte(reinterpret_cast<sockaddr *>(&sa), 5);

    EXPECT_EQ(actual, 0);

    actual = sa_get_address_byte(reinterpret_cast<sockaddr *>(&sa), 6);

    EXPECT_EQ(actual, 0);

    actual = sa_get_address_byte(reinterpret_cast<sockaddr *>(&sa), 7);

    EXPECT_EQ(actual, 0);

    actual = sa_get_address_byte(reinterpret_cast<sockaddr *>(&sa), 8);

    EXPECT_EQ(actual, 0);

    actual = sa_get_address_byte(reinterpret_cast<sockaddr *>(&sa), 9);

    EXPECT_EQ(actual, 0);

    actual = sa_get_address_byte(reinterpret_cast<sockaddr *>(&sa), 10);

    EXPECT_EQ(actual, 0xff);

    actual = sa_get_address_byte(reinterpret_cast<sockaddr *>(&sa), 11);

    EXPECT_EQ(actual, 0xff);

    actual = sa_get_address_byte(reinterpret_cast<sockaddr *>(&sa), 12);

    EXPECT_EQ(actual, 1);

    actual = sa_get_address_byte(reinterpret_cast<sockaddr *>(&sa), 13);

    EXPECT_EQ(actual, 2);

    actual = sa_get_address_byte(reinterpret_cast<sockaddr *>(&sa), 14);

    EXPECT_EQ(actual, 3);

    actual = sa_get_address_byte(reinterpret_cast<sockaddr *>(&sa), 15);

    EXPECT_EQ(actual, 4);

    actual = sa_get_address_byte(reinterpret_cast<sockaddr *>(&sa), 16);

    EXPECT_EQ(actual, -1);

    actual = sa_get_address_byte(reinterpret_cast<sockaddr *>(&sa), -1);

    EXPECT_EQ(actual, -1);
}