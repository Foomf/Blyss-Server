#pragma once

#include <spdlog/spdlog.h>

#include "uv_exception.hpp"

namespace blyss::server
{
    inline void uv_checked(const int val)
    {
        if (val != 0)
        {
            throw uv_exception(val);
        }
    }

    inline void uv_warned(const int val) noexcept
    {
        if (val != 0)
        {
            spdlog::error("uv error: {0}", val);
        }
    }
}