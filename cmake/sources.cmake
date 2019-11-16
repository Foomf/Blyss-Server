set(BLYSS_SRCS )
set(BLYSS_HDRS )

# --------------------------------------------------------- #
# main.cpp                                                  #
# --------------------------------------------------------- #
ADD_SRC_ROOT(main)
ADD_CLASS_ROOT(server)
ADD_CLASS_ROOT(perf_watcher)
ADD_HDR_ROOT(uv_exception)
ADD_HDR_ROOT(uv_utils)
ADD_CLASS_ROOT(client)
ADD_CLASS_ROOT(packet_reader)

# --------------------------------------------------------- #
# Text files                                                #
# --------------------------------------------------------- #
EMBED_FILE("banner.txt" "include/banner.hpp" "banner_text")
