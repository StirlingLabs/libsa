#include <gtest/gtest.h>
#include "../common.h"
#include "../sa.h"

TEST(sa, ipv4) {
    const char *s = "1.2.3.4";

    sockaddr_in expected;
    expected.sin_family = AF_INET;
    expected.sin_port = htons(1000);
    EXPECT_EQ(inet_pton(AF_INET, s, &expected.sin_addr), 1);

    auto actual = reinterpret_cast<sockaddr_in *>( sa_ipv4(s, 1000));

    EXPECT_NE(actual, nullptr);

    EXPECT_EQ(actual->sin_family, expected.sin_family);

    EXPECT_EQ(*reinterpret_cast<unsigned *>(&actual->sin_addr), *reinterpret_cast<unsigned *>(&expected.sin_addr));

    EXPECT_EQ(actual->sin_port, expected.sin_port);

    sa_free(actual);
}