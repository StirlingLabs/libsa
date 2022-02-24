#include <gtest/gtest.h>
#include "common.h"
#include "sa.h"


TEST(sa, address_bytes_ipv4) {
    sockaddr_in sa;
    sa.sin_family = AF_INET;
    sa.sin_port = htons(1000);

    size_t byteCount = 0;

    auto *bytes = sa_address_bytes(reinterpret_cast<sockaddr *>(&sa), &byteCount);

    EXPECT_EQ(byteCount, sizeof(in_addr));
    EXPECT_EQ((void*)bytes, (void*)&sa.sin_addr);
}

TEST(sa, address_bytes_ipv6) {
    sockaddr_in6 sa;
    sa.sin6_family = AF_INET6;
    sa.sin6_port = htons(1000);

    size_t byteCount = 0;

    auto *bytes = sa_address_bytes(reinterpret_cast<sockaddr *>(&sa), &byteCount);

    EXPECT_EQ(byteCount, sizeof(in6_addr));
    EXPECT_EQ((void*)bytes, (void*)&sa.sin6_addr);
}

TEST(sa, address_bytes_unspec) {
    sockaddr_in6 sa;
    sa.sin6_family = AF_UNSPEC;
    sa.sin6_port = htons(1000);

    size_t byteCount = 0;

    auto *bytes = sa_address_bytes(reinterpret_cast<sockaddr *>(&sa), &byteCount);

    EXPECT_EQ((size_t)byteCount, (size_t)0);
    EXPECT_EQ((void*)bytes, nullptr);
}