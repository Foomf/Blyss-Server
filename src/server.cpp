#include "server.hpp"

#include <cstdint>
#include "spdlog/spdlog.h"

#include "protocol.pb.h"

#include "uv_utils.hpp"

namespace blyss::server
{
    const std::uint64_t ms_per_frame = 50;
    const std::uint64_t slow_warning_reset_ms = 5000;

    void timer_callback(uv_timer_t*);
    void on_new_connection(uv_stream_t* server, int status);
    void alloc_callback(uv_handle_t* client, size_t suggested_size, uv_buf_t* buf);
    void read_callback(uv_stream_t* client, ssize_t nread, const uv_buf_t* buf);
    void close_cb(uv_handle_t* client);

    server::server(uv_loop_t* loop)
        : loop_{ loop }
        , perf_watcher_{ loop, ms_per_frame, slow_warning_reset_ms }
    {
        spdlog::info("Server pushed to memory stack.");
        loop_->data = this;

        uv_checked(uv_tcp_init(loop, &server_));
        sockaddr_in address{};
        uv_checked(uv_ip4_addr("0.0.0.0", 3786, &address));
        uv_checked(uv_tcp_bind(&server_, reinterpret_cast<const struct sockaddr*>(&address), 0));
        uv_checked(uv_listen(reinterpret_cast<uv_stream_t*>(&server_), 20, on_new_connection));

        uv_checked(uv_timer_init(loop_, &frame_timer_));
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
    }

    void timer_callback(uv_timer_t* handle)
    {
        auto self = static_cast<server*>(handle->loop->data);
        self->frame();
    }

    void on_new_connection(uv_stream_t* server, int status)
    {
        spdlog::info("New connection!");
        if (status < 0)
        {
            spdlog::error("New connection error! {0}", uv_strerror(status));
            return;
        }

        auto client = new uv_tcp_t;
        try
        {
            uv_checked(uv_tcp_init(server->loop, client));
            uv_checked(uv_accept(server, reinterpret_cast<uv_stream_t*>(client)));
            uv_checked(uv_read_start(reinterpret_cast<uv_stream_t*>(client), alloc_callback, read_callback));
            spdlog::info("New connection ready!");
        }
        catch (const uv_exception& e)
        {
            spdlog::error("Client connection error! {0}", e.what());
            delete client;
        }

    }

    void alloc_callback(uv_handle_t* client, size_t suggested_size, uv_buf_t* buf)
    {
        buf->base = static_cast<char*>(std::malloc(suggested_size));
        spdlog::info("Allocated {0} bytes", suggested_size);
        buf->len = suggested_size;
    }

    void read_callback(uv_stream_t* client, ssize_t nread, const uv_buf_t* buf)
    {
        spdlog::info("Read callback!");
        try
        {
            if (nread < 0)
            {
                uv_checked(nread);
            }

            spdlog::info("{0} bytes read.", nread);

            Foo f;
            f.ParseFromArray(buf->base, nread);
            spdlog::info("Message: {0}", f.msg());

        }
        catch (const uv_exception& e)
        {
            spdlog::error("Read error! {0}", e.what());
            uv_checked(uv_read_stop(client));
            uv_close(reinterpret_cast<uv_handle_t*>(client), close_cb);
        }

        std::free(buf->base);
        spdlog::info("Freed {0} bytes", buf->len);
    }

    void close_cb(uv_handle_t* client)
    {
        spdlog::info("Close callback!");
        delete client;
    }

}
