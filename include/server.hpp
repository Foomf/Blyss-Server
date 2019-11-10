#pragma once

#include <cstdint>

#include <uv.h>

#include "perf_watcher.hpp"

namespace blyss::server
{
    class server
    {
        uv_loop_t loop_;
        uv_timer_t frame_timer_{};

        std::int64_t counter_ = 0;

        perf_watcher perf_watcher_;

    public:
        server();
        ~server();

        void frame();

        void run_forever();

        void stop();
    };
}
