#pragma once

#include <memory>
#include <cstdint>
#include <array>
#include <functional>

#include "packet_buffer.hpp"
#include "packet_type.hpp"

namespace blyss::server
{
    class server;
    class packet_switch
    {
        server* server_;
        std::array<void(*)(std::int16_t, const std::uint8_t*), packet_type_length> handlers_{};

    public:
        packet_switch(server* server);

        void read_packet(std::int32_t client_id, std::unique_ptr<packet_buffer> buff);
    };
}
