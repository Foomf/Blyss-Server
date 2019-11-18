#include <stdexcept>

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

    TEST(packet_buffer_tests, ctor_negativeLength_ShouldThrow)
    {
        std::uint8_t data = 0;
        ASSERT_THROW(packet_buffer(-10, &data), std::invalid_argument);
    }

    TEST(packet_buffer_tests, ctor_nullData_ShouldThrow)
    {
        ASSERT_THROW(packet_buffer(1, nullptr), std::invalid_argument);
    }

    TEST(packet_buffer_tests, ctor_data_shouldSetData)
    {
        std::uint8_t data[] = { 1,2,3,4,5 };
        const packet_buffer b(sizeof(data), reinterpret_cast<std::uint8_t*>(&data));
        ASSERT_EQ(5, b.get_length());

        for (auto ii = 0; ii < 5; ++ii)
        {
            EXPECT_EQ(data[ii], b.get_data()[ii]);
        }
    }

    TEST(packet_buffer_tests, ctor_data_shouldBeCopied)
    {
        std::uint8_t data[] = { 1,2,3,4,5 };
        const packet_buffer b(sizeof(data), reinterpret_cast<std::uint8_t*>(&data));
        ASSERT_NE(data, b.get_data());
    }
}
