#include "packet_reader.hpp"

#include <stdexcept>
#include <cstring>

#include <spdlog/spdlog.h>

namespace blyss::server
{
    void packet_reader::read(std::uint8_t* data, const ssize_t nread)
    {
        if (!data)
        {
            spdlog::error("packet_reader::read called with null data!");
            return;
        }

        if (nread < 0)
        {
            spdlog::error("packet_reader::read called with negative length!");
            return;
        }

        auto data_pos = 0;

        while (data_pos < nread)
        {
            const auto dest = buffer_.data() + buffer_pos_;
            const auto src = data + data_pos;

            if (has_length_read())
            {
                const auto length = packet_length();
                const auto bytes_to_read = min(length, nread - data_pos);
                std::memcpy(dest, src, bytes_to_read);
                buffer_pos_ += bytes_to_read;
                data_pos += bytes_to_read;

                if (is_complete())
                {
                    auto packet = std::make_unique<packet_buffer>(length, buffer_.data() + 4);
                    packets_.push(std::move(packet));
                    buffer_pos_ = 0;
                }
            }
            else
            {
                std::memcpy(dest, src, 4);
                buffer_pos_ += 4;
                data_pos += 4;
            }
        }
    }

    std::optional<std::unique_ptr<packet_buffer>> packet_reader::pop()
    {
        if (packets_.empty())
        {
            return {};
        }

        auto packet = std::move(packets_.front());
        packets_.pop();
        return packet;
    }

    std::uint32_t packet_reader::packet_length() const
    {
        return std::uint32_t(
            static_cast<unsigned char>(buffer_[3]) << 24 |
            static_cast<unsigned char>(buffer_[2]) << 16 |
            static_cast<unsigned char>(buffer_[1]) << 8 |
            static_cast<unsigned char>(buffer_[0]));
    }

    bool packet_reader::is_complete() const
    {
        return packet_length() == buffer_pos_ - 4;
    }

    bool packet_reader::has_length_read() const
    {
        return buffer_pos_ >= 4;
    }

}