#include "world/world.hpp"

namespace blyss::server::world
{
    const map& world::add_map(boost::uuids::uuid map_id, std::int32_t max_x, std::int32_t max_y, std::unique_ptr<std::vector<cell>> cells)
    {
        auto m = std::make_unique<map>(map_id, max_x, max_y, std::move(cells));
        const auto value = maps_.emplace(map_id, std::move(m));
        return *value.first->second;
    }

}