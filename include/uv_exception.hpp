#pragma once

#include <stdexcept>

#include <uv.h>

namespace blyss::server
{
    class uv_exception final : public std::exception
    {
    public:
        explicit uv_exception(const int code)
            : std::exception(uv_strerror(code))
        {
        }
    };
}
