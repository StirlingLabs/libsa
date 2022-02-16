#include <gtest/gtest.h>
#include "../common.h"
#include "../sa.h"

TEST(libsatest, test_sa_ipv4_to_str) {
    const char *expected = "1.2.3.4";

    sockaddr_in sa = {.sin_family = AF_INET, .sin_port = htons(1000)};
    EXPECT_EQ(inet_pton(AF_INET, expected, &sa.sin_addr), 1);

    auto actual = sa_ipv4_to_str(reinterpret_cast<sockaddr *>(&sa));

    EXPECT_NE(actual, nullptr);

    EXPECT_STREQ(actual, expected);

    delete actual;
}