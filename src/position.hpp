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

struct PositionState {
    Square       en_passant;
    std::uint8_t rule50;
    Color        side_to_move;

    std::array<BitBoard, Color::COUNT()>     by_color;
    std::array<BitBoard, PieceType::COUNT()> by_piece_type;
    std::array<Piece, Square::COUNT()>       mailbox;

   private:
    Piece piece_on(const Square square) const noexcept;

    void add_piece(const Piece piece, const Square square) noexcept;
    void remove_piece(const Piece piece, const Square square) noexcept;

   public:
    constexpr PositionState& operator=(const PositionState& other) = default;

    constexpr PositionState() :
        en_passant{},
        rule50{},
        side_to_move{Color::WHITE()},
        by_color{},
        by_piece_type{},
        mailbox{} {};

    void make_move(const Move move) noexcept;

    static constexpr PositionState from_fen(std::string_view fen) noexcept;
};

}

#endif
