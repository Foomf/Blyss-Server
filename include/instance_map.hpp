#pragma once

#include <cstdint>
#include <memory>
#include <map>
#include <optional>

namespace blyss::server
{
    template<typename T>
    class instance_map
    {
        std::map<std::uintptr_t, std::unique_ptr<T>> instances_{};
        std::uintptr_t next_ref_ = 0;

    public:
        std::uintptr_t add_instance(std::unique_ptr<T> ptr)
        {
            auto idx = next_ref_++;
            instances_.emplace(idx, std::move(ptr));
            return idx;
        }

        std::optional<T&> get_instance(std::uintptr_t ref) const
        {
            auto it = instances_.find(ref);
            if (it == instances_.end())
            {
                return {};
            }

            return it->second;
        }

        void destroy(std::uintptr_t ref)
        {
            auto it = instances_.find(ref);
            if (it != instances_.end())
            {
                instances_.erase(it);
            }
        }
    };
}
