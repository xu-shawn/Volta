#ifndef VOLTA_POSITION_HPP__
#define VOLTA_POSITION_HPP__

#include <cstdint>

#include "bitboard.hpp"
#include "common.hpp"
#include "piece.hpp"

namespace Volta::Chess {

class PositionRecord {};

class Position {
    BitBoard byColor[Color::COUNT()];
    BitBoard byPiece[PieceType::COUNT()];

    void make_move()
};

}

#endif
