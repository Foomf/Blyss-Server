#include "world/world.hpp"

#include <stdexcept>

namespace blyss::server::world
{
    world::world(const std::int32_t max_x, const std::int32_t max_y, std::unique_ptr<std::vector<cell>> cells)
        : max_x_{max_x}
        , max_y_{max_y}
        , cells_{std::move(cells)}
    {
        
    }

    cell& world::cell_at(const std::int32_t x, const std::int32_t y) const
    {
        if (x < 0 || x > max_x_ || y < 0 || y > max_y_)
        {
            throw std::out_of_range("x or y is out of range!");
        }

        return cells_->at(x * max_x_ + y);
    }


}