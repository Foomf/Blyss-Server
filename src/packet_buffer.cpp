#include "packet_buffer.hpp"

#include <cstring>

namespace blyss::server
{
    packet_buffer::packet_buffer(std::uint8_t length, std::uint8_t* data)
        : length_{length}
        , buffer_{length}
    {
        std::memcpy(buffer_.data(), data, length);
    }
}