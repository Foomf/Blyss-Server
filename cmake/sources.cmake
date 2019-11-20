set(BLYSS_SRCS )
set(BLYSS_HDRS )

# --------------------------------------------------------- #
# main.cpp                                                  #
# --------------------------------------------------------- #
ADD_CLASS_ROOT(server)
ADD_CLASS_ROOT(perf_watcher)
ADD_HDR_ROOT(uv_exception)
ADD_HDR_ROOT(uv_utils)
ADD_CLASS_ROOT(client)
ADD_CLASS_ROOT(packet_reader)
ADD_CLASS_ROOT(packet_buffer)
ADD_CLASS_ROOT(packet_switch)
ADD_HDR_ROOT(packet_type)
ADD_HDR_ROOT(instance_map)

ADD_CLASS(world world)
ADD_CLASS(cell world)

# --------------------------------------------------------- #
# Text files                                                #
# --------------------------------------------------------- #
EMBED_FILE("banner.txt" "include/banner.hpp" "banner_text")
