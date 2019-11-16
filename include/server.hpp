#pragma once

#include <cstdint>
#include <stdexcept>
#include <vector>
#include <memory>

#include <uv.h>

#include "perf_watcher.hpp"

#include "client.hpp"

namespace blyss::server
{

    class server
    {
        uv_loop_t* loop_;
        uv_timer_t frame_timer_{};
        uv_tcp_t server_{};

        std::int32_t next_client_id_ = 0;

        std::int64_t counter_ = 0;

        perf_watcher perf_watcher_;

        std::vector<std::unique_ptr<client>> clients_;

    public:
        server(uv_loop_t* loop);
        ~server();

        void frame();

        void run_forever();

        void stop();

        void add_client(std::unique_ptr<client> c);

        std::int32_t gen_client_id();

        void cleanup_closed_clients();
    };
}
