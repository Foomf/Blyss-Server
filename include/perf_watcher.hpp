#pragma once

#include <cstdint>
#include <memory>

#include <uv.h>

namespace blyss::server
{
    class perf_watcher
    {
        bool show_slow_warning_ = false;
        uv_timer_t show_warning_timer_{};
        bool is_init_ = false;
        std::uint64_t ms_per_frame_;
        std::uint64_t slow_warning_reset_ms_;

        uv_loop_t* loop_ = nullptr;
        std::uint64_t previous_time_ = 0;

        void show_message(std::uint64_t missed_ms);

    public:
        perf_watcher(std::uint64_t ms_per_frame, std::uint64_t slow_warning_reset_ms);
        ~perf_watcher();

        perf_watcher(const perf_watcher&) = delete;
        perf_watcher(perf_watcher&&) = delete;
        perf_watcher& operator=(const perf_watcher&) = delete;
        perf_watcher& operator=(perf_watcher&&) = delete;

        void init(uv_loop_t* loop);

        void update();

        void reset();

        void start();
    };
}
