#include "world/world.hpp"

namespace blyss::server::world
{
    const map& world::add_map(boost::uuids::uuid map_id, std::int32_t max_x, std::int32_t max_y, std::unique_ptr<std::vector<cell>> cells)
    {
        const auto value = maps_.emplace(map_id, max_x, max_y, cells);
        return value.first->second;
    }

}