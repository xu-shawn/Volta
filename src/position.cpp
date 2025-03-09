#include <cstring>
#include <string_view>
#include <ranges>
#include <vector>
#include <iostream>

#include "attacks.hpp"
#include "bbmanip.hpp"
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
                remove_piece(Piece::make(PieceType::PAWN(), ~stm()), en_passant_destination_);
            }

            if (distance(from.rank(), to.rank()) == 2)
            {
                if (side_to_move == Color::WHITE())
                {
                    en_passant_destination_ = shift(to, Direction::SOUTH());
                }
                else
                {
                    en_passant_destination_ = shift(to, Direction::NORTH());
                }
            }

            rule50 = 0;
        }

        remove_piece(moved_piece, from);
        add_piece(moved_piece, to);
    }

    en_passant_destination_ = Square::NONE();

    side_to_move = ~side_to_move;
}

bool PositionState::is_legal() const noexcept { return true; }

bool PositionState::is_ok() const noexcept {
    const BitBoard king_bb = bb(Piece::make(PieceType::KING(), ~stm()));
    const Square   ksq     = Square::from_ordinal(king_bb.lsb());

    if (Attacks::pawn_attacks(king_bb, ~stm()) & bb(Piece::make(PieceType::PAWN(), stm())))
    {
        return false;
    }

    if (Attacks::knight_attacks(ksq) & bb(Piece::make(PieceType::KNIGHT(), stm())))
    {
        return false;
    }

    const BitBoard occ = bb(Color::WHITE(), Color::BLACK());

    if (Attacks::bishop_attacks(ksq, occ)
        & bb(Piece::make(PieceType::BISHOP(), stm()), Piece::make(PieceType::QUEEN(), stm())))
    {
        return false;
    }

    if (Attacks::rook_attacks(ksq, occ)
        & bb(Piece::make(PieceType::ROOK(), stm()), Piece::make(PieceType::QUEEN(), stm())))
    {
        return false;
    }

    return true;
}

std::ostream& operator<<(std::ostream& os, const PositionState& pos) {
    os << " +---+---+---+---+---+---+---+---+\n";

    for (int rank_idx = Rank::COUNT() - 1; rank_idx >= 0; rank_idx--)
    {
        for (int file_idx = File::COUNT() - 1; file_idx >= 0; file_idx--)
            os << " | "
               << pos.piece_on(Square(File::from_ordinal(file_idx), Rank::from_ordinal(rank_idx)))
                    .to_char();

        os << " | " << (1 + rank_idx) << "\n +---+---+---+---+---+---+---+---+\n";
    }

    os << "   a   b   c   d   e   f   g   h\n";

    return os;
}

}
