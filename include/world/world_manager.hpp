#pragma once

#include <map>

#include <boost/uuid/uuid.hpp>

#include "world.hpp"

namespace blyss::server::world
{
    class world_manager
    {
        std::map<boost::uuids::uuid, world> worlds_{};

    };
}