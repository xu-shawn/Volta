#ifndef VOLTA_BBMANIP_HPP
#define VOLTA_BBMANIP_HPP

#include "bitboard.hpp"
#include "coordinates.hpp"
#include "utility.hpp"
#include <stdexcept>

namespace Volta::Chess {

[[nodiscard]] inline constexpr BitBoard shift(const BitBoard bb, const Direction dir) {
    if (dir == Direction::NORTH())
        return bb << 8;

    if (dir == Direction::SOUTH())
        return bb >> 8;

    if (dir == Direction::EAST())
        return (bb & ~File::FILE_H().to_bb()) << 1;

    if (dir == Direction::WEST())
        return (bb & ~File::FILE_A().to_bb()) >> 1;

    if (dir == Direction::NORTH_EAST())
        return (bb & ~File::FILE_H().to_bb()) << 9;

    if (dir == Direction::SOUTH_EAST())
        return (bb & ~File::FILE_H().to_bb()) >> 7;

    if (dir == Direction::NORTH_WEST())
        return (bb & ~File::FILE_A().to_bb()) << 7;

    if (dir == Direction::SOUTH_WEST())
        return (bb & ~File::FILE_A().to_bb()) >> 9;

    assert(false);
}

template<typename T, typename... Ts>
[[nodiscard]] constexpr BitBoard shift(const BitBoard bb, const T dir, const Ts... dirs) {
    return shift(shift(bb, dir), dirs...);
}

[[nodiscard]] constexpr Square shift(const Square sq, const Direction dir) {
    if (dir == Direction::NORTH())
        return Square::from_ordinal(sq.to_underlying() + 8);

    if (dir == Direction::SOUTH())
        return Square::from_ordinal(sq.to_underlying() - 8);

    if (dir == Direction::EAST())
        return Square::from_ordinal(sq.to_underlying() + 1);

    if (dir == Direction::WEST())
        return Square::from_ordinal(sq.to_underlying() - 1);

    assert(false);
}

template<typename T, typename... Ts>
[[nodiscard]] constexpr Square shift(const Square sq, const T dir, const Ts... dirs) {
    return shift(shift(sq, dir), dirs...);
}

}

#endif
