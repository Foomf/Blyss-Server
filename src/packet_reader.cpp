#include "packet_reader.hpp"

#include <stdexcept>

namespace blyss::server
{
    void packet_reader::read(std::uint8_t* data, ssize_t nread)
    {
        if (packet_length_ == 0)
        {
            if (nread < sizeof(packet_length_))
            {
                throw std::exception("Cannot read packet length!");
            }


        }
    }

}