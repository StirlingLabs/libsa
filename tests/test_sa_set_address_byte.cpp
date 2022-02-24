#include <gtest/gtest.h>
#include "common.h"
#include "sa.h"

TEST(sa, set_address_byte_ipv4) {
    sockaddr_in sa;
    sa.sin_family = AF_INET;
    sa.sin_port = htons(1000);

    EXPECT_EQ(inet_pton(AF_INET, "1.2.3.4", &sa.sin_addr), 1);

    auto success = sa_set_address_byte(reinterpret_cast<sockaddr *>(&sa), 0, 5);

    EXPECT_EQ(success, true);

    success = sa_set_address_byte(reinterpret_cast<sockaddr *>(&sa), 1, 6);

    EXPECT_EQ(success, true);

    success = sa_set_address_byte(reinterpret_cast<sockaddr *>(&sa), 2, 7);

    EXPECT_EQ(success, true);

    success = sa_set_address_byte(reinterpret_cast<sockaddr *>(&sa), 3, 8);

    EXPECT_EQ(success, true);

    success = sa_set_address_byte(reinterpret_cast<sockaddr *>(&sa), 4, 9);

    EXPECT_EQ(success, false);

    success = sa_set_address_byte(reinterpret_cast<sockaddr *>(&sa), -1, 10);

    EXPECT_EQ(success, false);

    auto actual = sa_address_to_str(reinterpret_cast<sockaddr *>(&sa));

    EXPECT_STREQ(actual, "5.6.7.8");

    sa_free(actual);
}

TEST(sa, set_address_byte_ipv6) {
    sockaddr_in6 sa;
    sa.sin6_family = AF_INET6;
    sa.sin6_port = htons(1000);

    EXPECT_EQ(inet_pton(AF_INET6, "::ffff:0102:0304", &sa.sin6_addr), 1);

    auto success = sa_set_address_byte(reinterpret_cast<sockaddr *>(&sa), 0, 0xf0);

    EXPECT_EQ(success, true);

    success = sa_set_address_byte(reinterpret_cast<sockaddr *>(&sa), 1, 0xf1);

    EXPECT_EQ(success, true);

    success = sa_set_address_byte(reinterpret_cast<sockaddr *>(&sa), 2, 0xf2);

    EXPECT_EQ(success, true);

    success = sa_set_address_byte(reinterpret_cast<sockaddr *>(&sa), 3, 0xf3);

    EXPECT_EQ(success, true);

    success = sa_set_address_byte(reinterpret_cast<sockaddr *>(&sa), 4, 0xf4);

    EXPECT_EQ(success, true);

    success = sa_set_address_byte(reinterpret_cast<sockaddr *>(&sa), 5, 0xf5);

    EXPECT_EQ(success, true);

    success = sa_set_address_byte(reinterpret_cast<sockaddr *>(&sa), 6, 0xf6);

    EXPECT_EQ(success, true);

    success = sa_set_address_byte(reinterpret_cast<sockaddr *>(&sa), 7, 0xf7);

    EXPECT_EQ(success, true);

    success = sa_set_address_byte(reinterpret_cast<sockaddr *>(&sa), 8, 0xf8);

    EXPECT_EQ(success, true);

    success = sa_set_address_byte(reinterpret_cast<sockaddr *>(&sa), 9, 0xf9);

    EXPECT_EQ(success, true);

    success = sa_set_address_byte(reinterpret_cast<sockaddr *>(&sa), 10, 0xfa);

    EXPECT_EQ(success, true);

    success = sa_set_address_byte(reinterpret_cast<sockaddr *>(&sa), 11, 0xfb);

    EXPECT_EQ(success, true);

    success = sa_set_address_byte(reinterpret_cast<sockaddr *>(&sa), 12, 0xfc);

    EXPECT_EQ(success, true);

    success = sa_set_address_byte(reinterpret_cast<sockaddr *>(&sa), 13, 0xfd);

    EXPECT_EQ(success, true);

    success = sa_set_address_byte(reinterpret_cast<sockaddr *>(&sa), 14, 0xfe);

    EXPECT_EQ(success, true);

    success = sa_set_address_byte(reinterpret_cast<sockaddr *>(&sa), 15, 0xff);

    EXPECT_EQ(success, true);

    success = sa_set_address_byte(reinterpret_cast<sockaddr *>(&sa), 16, 0xc1);

    EXPECT_EQ(success, false);

    success = sa_set_address_byte(reinterpret_cast<sockaddr *>(&sa), -1, 0xc2);

    EXPECT_EQ(success, false);

    auto actual = sa_address_to_str(reinterpret_cast<sockaddr *>(&sa));

    EXPECT_STREQ(actual, "f0f1:f2f3:f4f5:f6f7:f8f9:fafb:fcfd:feff");

    sa_free(actual);
}