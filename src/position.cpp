#include <cstring>

#include "move.hpp"
#include "position.hpp"

namespace Volta::Chess {

Piece Position::piece_on(const Square square) const noexcept { return mailbox[square.ordinal()]; }

void Position::add_piece(const Piece piece, const Square square) noexcept {
    assert(piece.is_valid());
    assert(square.is_valid());

    const Color     color      = piece.color();
    const PieceType piece_type = piece.type();

    by_color[color.to_underlying()].set(square.ordinal());
    by_piece_type[piece_type.to_underlying()].set(square.ordinal());
    mailbox[square.ordinal()] = piece;
}

void Position::remove_piece(const Piece piece, const Square square) noexcept {
    assert(piece.is_valid());
    assert(square.is_valid());

    const Color     color      = piece.color();
    const PieceType piece_type = piece.type();

    by_color[color.to_underlying()].clear(square.ordinal());
    by_piece_type[piece_type.to_underlying()].clear(square.ordinal());
    mailbox[square.ordinal()] = Piece::NONE();
}

void Position::make_move(PositionRecord* const new_record, const Move move) noexcept {
    std::memcpy(new_record, record, sizeof(PositionRecord));
    new_record->previous = record;
    record               = new_record;

    const Square from           = move.from();
    const Square to             = move.to();
    const Piece  moved_piece    = piece_on(move.from());
    Piece        captured_piece = piece_on(move.to());

    if (move.is_castling())
    {
        // unimplemented
    }
}

}
