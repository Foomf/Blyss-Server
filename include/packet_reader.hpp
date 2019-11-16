#pragma once

#include <cstdint>

#include <uv.h>

#include "server.hpp"

namespace blyss::server
{
    class packet_reader
    {
        std::uint32_t packet_length_ = 0;
        server* server_;

        void read(std::uint8_t* data, ssize_t length);
    };
}