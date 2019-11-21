#pragma once

#include <vector>
#include <cstdint>
#include <memory>

#include "cell.hpp"

#include  <boost/uuid/uuid.hpp>

namespace blyss::server::world
{
    class map
    {
        std::int32_t max_x_;
        std::int32_t max_y_;

        std::unique_ptr<std::vector<cell>> cells_;

        boost::uuids::uuid map_id_;

    public:
        map(boost::uuids::uuid map_id, std::int32_t max_x, std::int32_t max_y, std::unique_ptr<std::vector<cell>> cells);

        [[nodiscard]] cell& cell_at(std::int32_t x, std::int32_t y) const;
    };
}