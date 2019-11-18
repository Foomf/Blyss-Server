#include <gtest/gtest.h>

#include "packet_reader.hpp"

namespace blyss::server
{
    TEST(packet_reader_tests, read_nullData_shouldNotThrow)
    {
        packet_reader r;
        ASSERT_NO_THROW(r.read(nullptr, 0));
    }

    TEST(packet_reader_tests, read_negativeLength_shouldNotThrow)
    {
        packet_reader r;
        std::uint8_t data = 0;
        ASSERT_NO_THROW(r.read(&data, -10));
    }

    TEST(packet_reader_tests, read_zeroLength_shouldNotThrow)
    {
        packet_reader r;
        std::uint8_t data = 0;
        ASSERT_NO_THROW(r.read(&data, 0));
    }

    TEST(packet_reader_tests, read_incompleteData_shouldDoNothing)
    {
        packet_reader r;
        std::uint8_t data[] = { 5, 0, 0, 0, 1, 2, 3 };
        r.read(data, sizeof(data));
        ASSERT_FALSE(r.pop().has_value());
    }

    TEST(packet_reader_tests, read_completeData_shouldHaveValue)
    {
        packet_reader r;
        std::uint8_t data[] = { 5, 0, 0, 0, 1, 2, 3, 4, 5 };
        r.read(data, sizeof(data));
        const auto p_opt = r.pop();
        ASSERT_TRUE(p_opt.has_value());
        const auto p = p_opt->get();
        ASSERT_EQ(5, p->get_length());

        for (auto ii = 0; ii < 5; ++ii)
        {
            EXPECT_EQ(ii + 1, p->get_data()[ii]);
        }
    }

    TEST(packet_reader_tests, read_dataAndLengthSeparate_shouldHaveValue)
    {
        packet_reader r;
        std::uint8_t length[] = { 5, 0, 0, 0 };
        std::uint8_t data[] = { 1, 2, 3, 4, 5 };
        r.read(length, sizeof(length));
        EXPECT_FALSE(r.pop().has_value());
        r.read(data, sizeof(data));

        const auto p_opt = r.pop();
        ASSERT_TRUE(p_opt.has_value());
        const auto p = p_opt->get();
        ASSERT_EQ(5, p->get_length());

        for (auto ii = 0; ii < 5; ++ii)
        {
            EXPECT_EQ(ii + 1, p->get_data()[ii]);
        }
    }

    TEST(packet_reader_tests, read_dataSplitInLength_shouldHaveValue)
    {
        packet_reader r;
        std::uint8_t d1[] = { 5, 0 };
        std::uint8_t d2[] = { 0, 0, 1, 2, 3, 4, 5 };
        r.read(d1, sizeof(d1));
        EXPECT_FALSE(r.pop().has_value());
        r.read(d2, sizeof(d2));

        const auto p_opt = r.pop();
        ASSERT_TRUE(p_opt.has_value());
        const auto p = p_opt->get();
        ASSERT_EQ(5, p->get_length());

        for (auto ii = 0; ii < 5; ++ii)
        {
            EXPECT_EQ(ii + 1, p->get_data()[ii]);
        }
    }

    TEST(packet_reader_tests, read_dataSplitInData_shouldHaveValue)
    {
        packet_reader r;
        std::uint8_t d1[] = { 5, 0, 0, 0, 1, 2 };
        std::uint8_t d2[] = { 3, 4, 5 };
        r.read(d1, sizeof(d1));
        EXPECT_FALSE(r.pop().has_value());
        r.read(d2, sizeof(d2));

        const auto p_opt = r.pop();
        ASSERT_TRUE(p_opt.has_value());
        const auto p = p_opt->get();
        ASSERT_EQ(5, p->get_length());

        for (auto ii = 0; ii < 5; ++ii)
        {
            EXPECT_EQ(ii + 1, p->get_data()[ii]);
        }
    }

    TEST(packet_reader_tests, read_multiData_shouldHaveValues)
    {
        packet_reader r;
        std::uint8_t data[] = { 5, 0, 0, 0, 1, 2, 3, 4, 5, 3, 0, 0, 0, 1, 2, 3 };
        r.read(data, sizeof(data));

        auto p_opt = r.pop();
        ASSERT_TRUE(p_opt.has_value());
        auto p = p_opt->get();
        ASSERT_EQ(5, p->get_length());

        for (auto ii = 0; ii < 5; ++ii)
        {
            EXPECT_EQ(ii + 1, p->get_data()[ii]);
        }

        p_opt = r.pop();
        ASSERT_TRUE(p_opt.has_value());
        p = p_opt->get();
        ASSERT_EQ(3, p->get_length());

        for (auto ii = 0; ii < 3; ++ii)
        {
            EXPECT_EQ(ii + 1, p->get_data()[ii]);
        }
    }

    TEST(packet_reader_tests, pop_emptyPackets_shouldReturnEmpty)
    {
        packet_reader r;
        ASSERT_FALSE(r.pop().has_value());
    }
}
