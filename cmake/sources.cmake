set(BLYSS_SRCS )
set(BLYSS_HDRS )

# --------------------------------------------------------- #
# main.cpp                                                  #
# --------------------------------------------------------- #
ADD_SRC_ROOT(main)
ADD_CLASS_ROOT(server)

# --------------------------------------------------------- #
# Text files                                                #
# --------------------------------------------------------- #
EMBED_FILE("banner.txt" "include/banner.hpp" "banner_text")
