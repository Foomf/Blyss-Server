#pragma once

#include <cstdint>

namespace blyss::server
{
    class packet_buffer final
    {
        std::int32_t length_;
        std::uint8_t* buffer_;

    public:
        packet_buffer(std::int32_t length, std::uint8_t* data);
        ~packet_buffer();

        packet_buffer(const packet_buffer&) = delete;
        packet_buffer(packet_buffer&&) = delete;
        packet_buffer& operator=(const packet_buffer&) = delete;
        packet_buffer& operator=(packet_buffer&&) = delete;

        [[nodiscard]] const std::uint8_t* get_data() const;
        [[nodiscard]] std::uint32_t get_length() const;
    };
}