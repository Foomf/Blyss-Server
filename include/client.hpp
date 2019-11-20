#pragma once

#include <cstdint>

#include <uv.h>

#include "packet_reader.hpp"
#include "instance_map.hpp"

namespace blyss::server
{
    class server;
    class client
    {
        std::int32_t client_id_;
        server* server_;

        uv_tcp_t handle_{};
        bool closed_ = false;
        packet_reader reader_{};
        instance_map<char*> buffers_{};
    public:
        client(uv_stream_t* server_handle, server* server, std::int32_t client_id);
        virtual ~client();

        [[nodiscard]] bool is_closed() const;
        void set_closed(bool closed);
        void close();
        [[nodiscard]] std::int32_t client_id() const;
        void read(std::uint8_t* data, ssize_t nread);
        void frame();
    };
}