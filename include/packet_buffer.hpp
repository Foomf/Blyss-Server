#pragma once

#include <cstdint>
#include <vector>

namespace blyss::server
{
    class packet_buffer
    {
        std::uint8_t length_;
        std::vector<std::uint8_t> buffer_;

    public:
        packet_buffer(std::uint8_t length, std::uint8_t* data);
    };
}