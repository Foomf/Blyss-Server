#pragma once

#include <map>

#include <boost/uuid/uuid.hpp>

#include "map.hpp"
#include "cell_ref.hpp"

namespace blyss::server::world
{
    class world
    {
        cell_ref spawn_location_{};

        std::map<boost::uuids::uuid, map> worlds_{};

    };
}