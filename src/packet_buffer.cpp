#include "packet_buffer.hpp"

#include <cstring>
#include <stdexcept>

namespace blyss::server
{
    packet_buffer::packet_buffer(const std::int32_t length, std::uint8_t* data)
        : length_{length}
        , buffer_{nullptr}
    {
        if (!data)
        {
            throw std::invalid_argument("data cannot be null!");
        }

        if (length < 0)
        {
            throw std::invalid_argument("length cannot be less than 0!");
        }

        buffer_ = new std::uint8_t[length];

        std::memcpy(buffer_, data, length);
    }

    packet_buffer::~packet_buffer()
    {
        delete[] buffer_;
    }

    const std::uint8_t* packet_buffer::get_data() const
    {
        return buffer_;
    }

    std::uint32_t packet_buffer::get_length() const
    {
        return length_;
    }
}
