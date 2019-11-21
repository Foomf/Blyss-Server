#include "server.hpp"

#include <cstdint>
#include "spdlog/spdlog.h"

#include "uv_utils.hpp"

#include "packet_buffer.hpp"

#include "world/cell.hpp"

#include <boost/uuid/uuid.hpp>

namespace blyss::server
{
    const std::uint64_t ms_per_frame = 50;
    const std::uint64_t slow_warning_reset_ms = 5000;

    void timer_callback(uv_timer_t*);
    void on_new_connection(uv_stream_t* server_handle, int status);

    server::server(uv_loop_t* loop)
        : loop_{ loop }
        , perf_watcher_{ loop, ms_per_frame, slow_warning_reset_ms }
        , switch_{this}
    {
        spdlog::info("Server pushed to memory stack.");
        loop_->data = this;

        uv_checked(uv_tcp_init(loop, &server_));
        sockaddr_in address{};
        uv_checked(uv_ip4_addr("0.0.0.0", 3786, &address));
        uv_checked(uv_tcp_bind(&server_, reinterpret_cast<const struct sockaddr*>(&address), 0));
        uv_checked(uv_listen(reinterpret_cast<uv_stream_t*>(&server_), 20, on_new_connection));

        uv_checked(uv_timer_init(loop_, &frame_timer_));

        world_ = make_null_world();
    }

    server::~server()
    {
        spdlog::info("Server removed from memory.");
    }

    void server::run_forever()
    {
        uv_checked(uv_timer_start(&frame_timer_, timer_callback, 0, ms_per_frame));
        perf_watcher_.start();

        spdlog::info("Main loop started!");
        uv_checked(uv_run(loop_, UV_RUN_DEFAULT));
        spdlog::info("Main loop stopped!");
    }

    void server::stop()
    {
        uv_checked(uv_timer_stop(&frame_timer_));
    }

    void server::frame()
    {
        perf_watcher_.update();

        for(auto& c : clients_)
        {
            c->frame();
        }
    }

    void server::add_client(std::unique_ptr<client> c)
    {
        clients_.push_back(std::move(c));
    }

    std::int32_t server::gen_client_id()
    {
        return next_client_id_++;
    }

    void server::remove_client(std::int32_t client_id)
    {
        clients_.erase(
            std::remove_if(clients_.begin(), clients_.end(), [=](const std::unique_ptr<client>& c) { return c->client_id() == client_id; }),
            clients_.end());
    }

    void server::read_packet(std::int32_t client_id, std::unique_ptr<packet_buffer> buff)
    {
        switch_.read_packet(client_id, std::move(buff));
    }

    std::unique_ptr<world::world> server::make_null_world()
    {
        const auto dim = 8;
        auto world = std::make_unique<world::world>();
        const boost::uuids::uuid map_id{};
        auto cells = std::make_unique<std::vector<world::cell>>();
        for (auto ii = 0; ii < dim * dim; ++ii)
        {
            cells->push_back(world::cell());
        }
        world->add_map(map_id, dim, dim, std::move(cells));
        return world;
    }

    void timer_callback(uv_timer_t* handle)
    {
        auto self = static_cast<server*>(handle->loop->data);
        self->frame();
    }

    void on_new_connection(uv_stream_t* server_handle, int status)
    {
        spdlog::info("New connection!");
        if (status < 0)
        {
            spdlog::error("New connection error! {0}", uv_strerror(status));
            return;
        }

        auto s = static_cast<server*>(server_handle->loop->data);
        auto id = s->gen_client_id();

        try
        {
            s->add_client(std::make_unique<client>(server_handle, s, id));
        }
        catch (const uv_exception & e)
        {
            spdlog::error("Client connection error! {0}", e.what());
        }
    }

}
