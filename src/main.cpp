#include <iostream>
#include <cstdio>
#include <stdexcept>

#include "spdlog/spdlog.h"

#include "server.hpp"

using namespace blyss::server;

int main()
{
    try
    {
        server s(uv_default_loop());
        s.run_forever();
        return EXIT_SUCCESS;
    }
    catch (std::exception& e)
    {
        spdlog::critical("Blyss Server crashed! What: {0}", e.what());
    }
    catch (...)
    {
        spdlog::critical("Blyss Server crashed with an unknown exception!");
    }

    return EXIT_FAILURE;
}