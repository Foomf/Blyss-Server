#include "client.hpp"

#include "uv_utils.hpp"
#include "protocol.pb.h"

namespace blyss::server
{
    void alloc_callback(uv_handle_t* client, size_t suggested_size, uv_buf_t* buf);
    void read_callback(uv_stream_t* client_handle, ssize_t nread, const uv_buf_t* buf);
    void close_cb(uv_handle_t* client);

    client::client(uv_stream_t* server, std::int32_t client_id)
        : client_id_{client_id}
    {
        uv_checked(uv_tcp_init(server->loop, &handle_));
        handle_.data = this;
        uv_checked(uv_accept(server, reinterpret_cast<uv_stream_t*>(&handle_)));
        uv_checked(uv_read_start(reinterpret_cast<uv_stream_t*>(&handle_), alloc_callback, read_callback));
        spdlog::info("New connection ready!");
    }

    client::~client()
    {
        spdlog::info("Client destroyed!");
    }

    bool client::is_closed() const
    {
        return closed_;
    }

    void client::set_closed(bool closed)
    {
        closed_ = closed;
    }

    void client::close()
    {
        const auto handle = reinterpret_cast<uv_handle_t*>(&handle_);
        if (!uv_is_closing(handle))
        {
            uv_close(handle, close_cb);
        }
    }

    void alloc_callback(uv_handle_t* client, size_t suggested_size, uv_buf_t* buf)
    {
        buf->base = static_cast<char*>(std::malloc(suggested_size));
        spdlog::info("Allocated {0} bytes", suggested_size);
        buf->len = suggested_size;
    }

    void read_callback(uv_stream_t* client_handle, ssize_t nread, const uv_buf_t* buf)
    {
        auto c = static_cast<client*>(client_handle->data);

        spdlog::info("Read callback!");
        try
        {
            if (nread == UV_EOF)
            {
                spdlog::info("Done reading from client_handle!");
                c->close();
                return;
            }

            if (nread < 0)
            {
                uv_checked(nread);
            }

            spdlog::info("{0} bytes read.", nread);
            Foo f;
            f.ParseFromArray(buf->base, nread);
            spdlog::info("Message: {0}", f.msg());
        }
        catch (const uv_exception & e)
        {
            spdlog::error("Read error! {0}", e.what());
            uv_checked(uv_read_stop(client_handle));
            uv_close(reinterpret_cast<uv_handle_t*>(client_handle), close_cb);
        }

        std::free(buf->base);
        spdlog::info("Freed {0} bytes", buf->len);
    }

    void close_cb(uv_handle_t* client_handle)
    {
        spdlog::info("Close callback!");
        auto c = static_cast<client*>(client_handle->data);
        c->set_closed(true);
    }

}