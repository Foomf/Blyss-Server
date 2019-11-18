#include "packet_switch.hpp"

#include <spdlog/spdlog.h>

#include "server.hpp"

#include "protocol.pb.h"

namespace blyss::server
{
    const std::uint8_t packet_header_length = 2;

    void handle_foo(server*, std::int32_t, std::int16_t, const std::uint8_t*);

    packet_switch::packet_switch(server* server)
        : server_{ server }
    {
        std::memset(handlers_.data(), 0, handlers_.size());
        handlers_[foo] = &handle_foo;
    }

    void packet_switch::read_packet(std::int32_t client_id, std::unique_ptr<packet_buffer> buff)
    {
        auto buffer = buff->get_data();
        auto length = buff->get_length();

        if (length < packet_header_length)
        {
            spdlog::warn("Read a packet with no packet id from client {0}!", client_id);
            return;
        }

        const auto packet_id = std::uint16_t(
            static_cast<unsigned char>(buffer[1]) << 8 |
            static_cast<unsigned char>(buffer[0]));

        buffer += packet_header_length;
        length -= packet_header_length;

        if (packet_id < 0 || packet_id >= packet_type_length)
        {
            spdlog::warn("Read unknown packet of id {0} from client {1}", packet_id, client_id);
            return;
        }

        const auto handler = handlers_[packet_id];
        if (!handler)
        {
            spdlog::error("No handler found for packet {0}!", packet_id);
            return;
        }

        handler(server_, client_id, length, buffer);
    }

    void handle_foo(server* s, std::int32_t client_id, std::int16_t length, const std::uint8_t* data)
    {
        Foo f;
        f.ParseFromArray(data, length);
        spdlog::info("Message: {0}", f.msg());
    }

}
