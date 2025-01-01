#ifndef VOLTA_COMMON_HPP__
#define VOLTA_COMMON_HPP__

#include <cstdint>

namespace Volta::Chess {

enum class Direction : std::int8_t {
    NORTH = 8,
    EAST  = 1,
    SOUTH = -NORTH,
    WEST  = -EAST,

    NORTH_EAST = NORTH + EAST,
    SOUTH_EAST = SOUTH + EAST,
    SOUTH_WEST = SOUTH + WEST,
    NORTH_WEST = NORTH + WEST
};

}

#endif
