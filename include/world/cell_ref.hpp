#pragma once

#include <cstdint>

#include <boost/uuid/uuid.hpp>

namespace blyss::server::world
{
    struct cell_ref
    {
        std::int32_t x;
        std::int32_t y;
        boost::uuids::uuid world_id;
    };
}