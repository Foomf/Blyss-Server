#pragma once

#include <cstdint>
#include <array>
#include <queue>
#include <memory>
#include <optional>

#include <uv.h>

#include "packet_buffer.hpp"

namespace blyss::server
{
    class packet_reader
    {
        static const std::uint16_t max_packet_length = 5000;

        std::array<std::uint8_t, max_packet_length> buffer_{};
        std::uint16_t buffer_pos_ = 0;
        std::queue<std::unique_ptr<packet_buffer>> packets_{};

        [[nodiscard]] bool has_length_read() const;

        [[nodiscard]] std::uint32_t packet_length() const;

        [[nodiscard]] bool is_complete() const;

    public:
        void read(std::uint8_t* data, ssize_t nread);

        std::optional<std::unique_ptr<packet_buffer>> pop();
    };
}