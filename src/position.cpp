#include <cstring>
#include <string_view>
#include <ranges>
#include <vector>
#include <iostream>

#include "common.hpp"
#include "coordinates.hpp"
#include "move.hpp"
#include "piece.hpp"
#include "position.hpp"
#include "utility.hpp"

namespace Volta::Chess {

Piece PositionState::piece_on(const Square square) const noexcept {
    return mailbox[square.ordinal()];
}

void PositionState::add_piece(const Piece piece, const Square square) noexcept {
    assert(piece.is_valid());
    assert(square.is_valid());

    const Color     color      = piece.color();
    const PieceType piece_type = piece.type();

    by_color[color.to_underlying()].set(square.ordinal());
    by_piece_type[piece_type.to_underlying()].set(square.ordinal());
    mailbox[square.ordinal()] = piece;
}

void PositionState::remove_piece(const Piece piece, const Square square) noexcept {
    assert(piece.is_valid());
    assert(square.is_valid());

    const Color     color      = piece.color();
    const PieceType piece_type = piece.type();

    by_color[color.to_underlying()].clear(square.ordinal());
    by_piece_type[piece_type.to_underlying()].clear(square.ordinal());
    mailbox[square.ordinal()] = Piece::NONE();
}

void PositionState::make_move(const Move move) noexcept {

    const Square from           = move.from();
    const Square to             = move.to();
    const Piece  moved_piece    = piece_on(move.from());
    const Piece  captured_piece = piece_on(move.to());

    rule50++;

    if (move.is_castling())
    {
        // unimplemented
    }
    else
    {
        if (captured_piece.is_valid())
        {
            remove_piece(captured_piece, to);
            rule50 = 0;
        }
        if (moved_piece.type() == PieceType::PAWN())
        {
            if (move.is_ep())
            {
                remove_piece(Piece::make(PieceType::PAWN(), ~side_to_move), en_passant);
                rule50 = 0;
            }

            if (distance(from.rank(), to.rank()) == 2)
            {
                if (side_to_move == Color::WHITE())
                    en_passant = shift<Direction::SOUTH()>(to);
                else  // if (side_to_move == Color::BLACK())
                    en_passant = shift<Direction::NORTH()>(to);
            }

            rule50 = 0;
        }

        remove_piece(moved_piece, from);
        add_piece(moved_piece, to);
    }

    en_passant = Square::NONE();

    side_to_move = ~side_to_move;
}

}
