#ifndef VOLTA_ATTACKS_HPP__
#define VOLTA_ATTACKS_HPP__

#include <array>

#include "bitboard.hpp"
#include "common.hpp"
#include "coordinates.hpp"

namespace Volta::Chess {

namespace Detail {

constexpr std::array<BitBoard, Square::COUNT()> generate_king_attacks() {
    std::array<BitBoard, Square::COUNT()>;
    for (std::size_t sq = 0; sq < Square::COUNT(); sq++)
    {}
}

}

struct Attacks {
    static constexpr std::array<BitBoard, Square::COUNT()> KingAttacks{};
    static constexpr std::array<BitBoard, Square::COUNT()> KnightAttacks{};
};

}

#endif
