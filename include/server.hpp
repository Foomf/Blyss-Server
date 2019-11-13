#pragma once

#include <cstdint>
#include <stdexcept>

#include <uv.h>

#include "perf_watcher.hpp"

namespace blyss::server
{
    class server
    {
        uv_loop_t* loop_;
        uv_timer_t frame_timer_{};
        uv_tcp_t server_{};

        std::int64_t counter_ = 0;

        perf_watcher perf_watcher_;

    public:
        server(uv_loop_t* loop);
        ~server();

        void frame();

        void run_forever();

        void stop();
    };
}
