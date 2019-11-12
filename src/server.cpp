#include "server.hpp"

#include <cstdint>
#include "spdlog/spdlog.h"

namespace blyss::server
{
    const std::uint64_t ms_per_frame = 50;

    void timer_callback(uv_timer_t*);

    server::server(uv_loop_t* loop)
        : loop_{loop}
        , perf_watcher_{loop, ms_per_frame, 5000}
    {
        spdlog::info("Server pushed to memory stack.");
        loop_->data = this;

        uv_timer_init(loop_, &frame_timer_);
    }

    server::~server()
    {
        uv_loop_close(loop_);
        spdlog::info("Server removed from memory.");
    }

    void server::run_forever()
    {
        uv_timer_start(&frame_timer_, timer_callback, 0, ms_per_frame + 50);
        perf_watcher_.start();

        spdlog::info("Main loop started!");
        uv_run(loop_, UV_RUN_DEFAULT);
        spdlog::info("Main loop stopped!");
    }

    void server::stop()
    {
        uv_timer_stop(&frame_timer_);
    }

    void server::frame()
    {
        perf_watcher_.update();
    }

    void timer_callback(uv_timer_t* handle)
    {
        auto self = static_cast<server*>(handle->loop->data);
        self->frame();
    }

}
