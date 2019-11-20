#pragma once

#include <vector>
#include <cstdint>
#include <memory>

#include "cell.hpp"

namespace blyss::server::world
{
    class world
    {
        std::int32_t max_x_;
        std::int32_t max_y_;

        std::unique_ptr<std::vector<cell>> cells_;

    public:
        world(std::int32_t max_x, std::int32_t max_y, std::unique_ptr<std::vector<cell>> cells);

        [[nodiscard]] cell& cell_at(std::int32_t x, std::int32_t y) const;
    };
}