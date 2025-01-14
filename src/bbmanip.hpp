#ifndef VOLTA_BBMANIP_HPP
#define VOLTA_BBMANIP_HPP

#include "bitboard.hpp"
#include "coordinates.hpp"

namespace Volta::Chess {

template<Direction::underlying dir>
[[nodiscard]] constexpr BitBoard shift(BitBoard bb) {
    if constexpr (dir == Direction::underlying::NORTH)
        return bb << 8;

    if constexpr (dir == Direction::underlying::SOUTH)
        return bb >> 8;

    if constexpr (dir == Direction::underlying::EAST)
        return (bb & ~File::FILE_H().to_bb()) << 1;

    if constexpr (dir == Direction::underlying::WEST)
        return (bb & ~File::FILE_A().to_bb()) >> 1;

    if constexpr (dir == Direction::underlying::NORTH_EAST)
        return (bb & ~File::FILE_H().to_bb()) << 9;

    if constexpr (dir == Direction::underlying::SOUTH_EAST)
        return (bb & ~File::FILE_H().to_bb()) >> 7;

    if constexpr (dir == Direction::underlying::NORTH_WEST)
        return (bb & ~File::FILE_A().to_bb()) << 7;

    if constexpr (dir == Direction::underlying::SOUTH_WEST)
        return (bb & ~File::FILE_A().to_bb()) >> 9;
}

}

#endif
