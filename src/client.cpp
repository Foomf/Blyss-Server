#include "client.hpp"

#include "uv_utils.hpp"
#include "server.hpp"

namespace blyss::server
{
    void alloc_callback(uv_handle_t* client, size_t suggested_size, uv_buf_t* buf);
    void read_callback(uv_stream_t* client_handle, ssize_t nread, const uv_buf_t* buf);
    void close_cb(uv_handle_t* client);

    client::client(uv_stream_t* server_handle, server* server, std::int32_t client_id)
        : client_id_{client_id}
        , server_{server}
    {
        uv_checked(uv_tcp_init(server_handle->loop, &handle_));
        handle_.data = this;
        uv_checked(uv_accept(server_handle, reinterpret_cast<uv_stream_t*>(&handle_)));
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

    std::int32_t client::client_id() const
    {
        return client_id_;
    }

    void client::read(std::uint8_t* data, ssize_t nread)
    {
        reader_.read(data, nread);
    }

    void client::frame()
    {
        std::optional<std::unique_ptr<packet_buffer>> p_opt;
        while (p_opt = reader_.pop(), p_opt.has_value())
        {
            server_->read_packet(client_id_, std::move(p_opt.value()));
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
            }
            else if (nread < 0)
            {
                uv_checked(nread);
            }
            else
            {
                spdlog::info("{0} bytes read.", nread);
                c->read(reinterpret_cast<std::uint8_t*>(buf->base), nread);
            }
        }
        catch (const std::exception& e)
        {
            spdlog::error("Read error for client {0}! {1}", c->client_id(), e.what());
            c->close();
        }

        std::free(buf->base);
        spdlog::info("Freed {0} bytes", buf->len);
    }

    void close_cb(uv_handle_t* client_handle)
    {
        spdlog::info("Close callback!");
        auto c = static_cast<client*>(client_handle->data);
        auto s = static_cast<server*>(client_handle->loop->data);
        c->set_closed(true);
        s->remove_client(c->client_id());
    }

}