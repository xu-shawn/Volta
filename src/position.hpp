#ifndef VOLTA_POSITION_HPP__
#define VOLTA_POSITION_HPP__

#include <array>
#include <cstdint>

#include "bitboard.hpp"
#include "common.hpp"
#include "coordinates.hpp"
#include "move.hpp"
#include "piece.hpp"

namespace Volta::Chess {

// Copy-Make properties of Position
struct PositionRecord {
    Square            en_passant;
    std::uint_fast8_t rule50;
    PositionRecord*   previous;
};

class Position {
   private:
    Color side_to_move;

    std::array<BitBoard, Color::COUNT()>     by_color;
    std::array<BitBoard, PieceType::COUNT()> by_piece_type;
    std::array<Piece, Square::COUNT()>       mailbox;

    PositionRecord* record;

    Piece piece_on(const Square square) const noexcept;

    void add_piece(const Piece piece, const Square square) noexcept;
    void remove_piece(const Piece piece, const Square square) noexcept;

   public:
    void make_move(PositionRecord* const record, const Move move) noexcept;
    void undo_move(const Move move) noexcept;
};
}

#endif
