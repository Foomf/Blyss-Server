#include <gtest/gtest.h>

#include "packet_buffer.hpp"

namespace blyss::server
{
    TEST(packet_buffer_tests, ctor_zeroLength_LengthShouldBeZero)
    {
        std::uint8_t data = 0;
        const packet_buffer b(0, &data);
        EXPECT_EQ(0, b.get_length()) << "Packet is not length 0!";
    }
}
