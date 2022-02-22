#include <gtest/gtest.h>
#include "../common.h"
#include "../sa.h"

TEST(sa, set_family_unspec) {
    sockaddr_in sa;
    sa.sin_family = AF_INET;
    sa.sin_port = htons(1000);

    sa_set_family(reinterpret_cast<sockaddr *>(&sa), AF_UNSPEC);

    EXPECT_EQ(sa.sin_family, AF_UNSPEC);
}

TEST(sa, set_family_ipv4) {
    sockaddr_in sa;
    sa.sin_family = AF_UNSPEC;
    sa.sin_port = htons(1000);

    sa_set_family(reinterpret_cast<sockaddr *>(&sa), AF_INET);

    EXPECT_EQ(sa.sin_family, AF_INET);
}

TEST(sa, set_family_ipv6) {
    sockaddr_in6 sa;
    sa.sin6_family = AF_UNSPEC;
    sa.sin6_port = htons(1000);

    sa_set_family(reinterpret_cast<sockaddr *>(&sa), AF_INET6);

    EXPECT_EQ(sa.sin6_family, AF_INET6);
}