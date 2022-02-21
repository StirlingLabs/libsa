#include <gtest/gtest.h>
#include "../common.h"
#include "../sa.h"

TEST(sa, get_size_ipv4) {
    sockaddr_in sa;
    sa.sin_family = AF_INET;
    sa.sin_port = htons(1000);

    auto actual = sa_get_size(reinterpret_cast<sockaddr *>(&sa));

    EXPECT_EQ(actual, sizeof(sockaddr_in));

    EXPECT_EQ(sa_get_size_ipv4(), sizeof(sockaddr_in));

    EXPECT_EQ(sa_get_size_by_family(AF_INET), sizeof(sockaddr_in));
}

TEST(sa, get_size_ipv6) {
    sockaddr_in6 sa;
    sa.sin6_family = AF_INET6;
    sa.sin6_port = htons(1000);

    auto actual = sa_get_size(reinterpret_cast<sockaddr *>(&sa));

    EXPECT_EQ(actual, sizeof(sockaddr_in6));

    EXPECT_EQ(sa_get_size_ipv6(), sizeof(sockaddr_in6));

    EXPECT_EQ(sa_get_size_by_family(AF_INET6), sizeof(sockaddr_in6));
}

TEST(sa, get_size_unspec) {
    sockaddr_in6 sa;
    sa.sin6_family = AF_UNSPEC;
    sa.sin6_port = htons(1000);

    auto actual = sa_get_size(reinterpret_cast<sockaddr *>(&sa));

    EXPECT_EQ(actual, sizeof(sockaddr_in6));

    EXPECT_EQ(sa_get_size_unspec(), sizeof(sockaddr_in6));

    EXPECT_EQ(sa_get_size_by_family(AF_UNSPEC), sizeof(sockaddr_in6));
}

TEST(sa, get_size_storage) {
    sockaddr_storage sa;
    sa.ss_family = (sa_family_t)UINT16_MAX;

    auto actual = sa_get_size(reinterpret_cast<sockaddr *>(&sa));

    EXPECT_EQ(actual, sizeof(sockaddr_storage));

    EXPECT_EQ(sa_get_size_storage(), sizeof(sockaddr_storage));

    EXPECT_EQ(sa_get_size_by_family(UINT16_MAX), sizeof(sockaddr_storage));
}
