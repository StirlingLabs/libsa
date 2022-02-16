#include <gtest/gtest.h>
#include "../common.h"
#include "../sa.h"

TEST(libsatest, test_sa_set_port_ipv4_1) {
    sockaddr_in sa{.sin_family = AF_INET, .sin_port = htons(1000)};

    EXPECT_EQ(inet_pton(AF_INET, "1.2.3.4", &sa.sin_addr), 1);

    char scopeNameBuffer[IF_NAMESIZE];
    auto scope = if_indextoname(1, scopeNameBuffer);

    EXPECT_FALSE(sa_set_scope(reinterpret_cast<sockaddr *>(&sa), scope));
}

TEST(libsatest, test_sa_set_port_ipv6_1) {
    sockaddr_in6 sa{.sin6_family = AF_INET6, .sin6_port = htons(1000)};

    EXPECT_EQ(inet_pton(AF_INET6, "::ffff:0102:0304", &sa.sin6_addr), 1);

    char scopeNameBuffer[IF_NAMESIZE];
    auto scope = if_indextoname(1, scopeNameBuffer);

    EXPECT_TRUE(sa_set_scope(reinterpret_cast<sockaddr *>(&sa), scope));

    EXPECT_EQ(sa.sin6_scope_id, 1);
}