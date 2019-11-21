#pragma once

#include <map>

#include <boost/uuid/uuid.hpp>

#include "map.hpp"
#include "cell.hpp"
#include "cell_ref.hpp"

namespace blyss::server::world
{
    class world
    {
        cell_ref spawn_location_{};

        std::map<boost::uuids::uuid, map> maps_{};

    public:
        const map& add_map(boost::uuids::uuid map_id, std::int32_t max_x, std::int32_t max_y, std::unique_ptr<std::vector<cell>> cells);
    };
}