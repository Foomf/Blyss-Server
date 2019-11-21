#pragma once

#include <map>

#include <boost/uuid/uuid.hpp>

#include "map.hpp"

namespace blyss::server::world
{
    class world
    {
        std::map<boost::uuids::uuid, map> worlds_{};

    };
}