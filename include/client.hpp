#pragma once

#include <cstdint>

#include <uv.h>

namespace blyss::server
{
    class client
    {
        std::int32_t client_id_;
        uv_tcp_t handle_{};
        bool closed_ = false;

    public:
        client(uv_stream_t* server, std::int32_t client_id);
        virtual ~client();

        bool is_closed() const;
        void set_closed(bool closed);
        void close();
        std::int32_t client_id() const;
    };
}