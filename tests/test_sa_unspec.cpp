#include <gtest/gtest.h>
#include "common.h"
#include "sa.h"

TEST(sa, unspec) {
    sockaddr_in6 expected;
    expected.sin6_family = AF_UNSPEC;
    expected.sin6_port = htons(1000);

    auto actual = reinterpret_cast<sockaddr_in6 *>( sa_unspec(1000));

    EXPECT_NE(actual, nullptr);

    EXPECT_EQ(actual->sin6_family, expected.sin6_family);

    EXPECT_EQ(actual->sin6_port, expected.sin6_port);

    sa_free(actual);
}