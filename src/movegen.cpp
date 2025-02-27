#include "movegen.hpp"

#include "attacks.hpp"
#include "bitboard.hpp"
#include "move.hpp"
#include "piece.hpp"

namespace Volta::Chess {

namespace {

void append_moves_from_sq_to_bb(MoveList&      movelist,
                                const Square   from,
                                BitBoard       bb,
                                const MoveFlag flag);

void append_pawn_moves(MoveList& movelist, const PositionState& pos, const Color side);
void append_knight_moves(MoveList& movelist, const PositionState& pos, const Color side);
void append_bishop_moves(MoveList& movelist, const PositionState& pos, const Color side);
void append_rook_moves(MoveList& movelist, const PositionState& pos, const Color side);
void append_queen_moves(MoveList& movelist, const PositionState& pos, const Color side);
void append_king_moves(MoveList& movelist, const PositionState& pos, const Color side);

}  // namespace

void append_all_moves(MoveList& movelist, const PositionState& pos, const Color side) {
    append_pawn_moves(movelist, pos, side);
    append_knight_moves(movelist, pos, side);
    append_bishop_moves(movelist, pos, side);
    append_rook_moves(movelist, pos, side);
    append_queen_moves(movelist, pos, side);
    append_king_moves(movelist, pos, side);
}

namespace {

void append_moves_from_sq_to_bb(MoveList&      movelist,
                                const Square   from,
                                BitBoard       bb,
                                const MoveFlag flag) {
    while (bb)
    {
        const Square to = Square::from_ordinal(bb.pop_lsb());
        movelist.push_back(Move(flag, from, to));
    }
}

void append_pawn_moves(MoveList& movelist, const PositionState& pos, const Color side) {
    const BitBoard  us_occ        = pos.bb(side);
    const BitBoard  them_occ      = pos.bb(~side);
    const BitBoard  occ           = us_occ & them_occ;
    const BitBoard  starting_rank = side == Color::WHITE() ? Rank::RANK_2() : Rank::RANK_7();
    const BitBoard  pawn_bb       = pos.bb(PieceType::PAWN()) & us_occ;
    const Direction push_dir = side == Color::WHITE() ? Direction::NORTH() : Direction::SOUTH();

    const BitBoard starting_pawns = us_occ & starting_rank;

    const BitBoard forward_push = shift(pawn_bb & occ, push_dir);
}

void append_knight_moves(MoveList& movelist, const PositionState& pos, const Color side) {
    const BitBoard us_occ   = pos.bb(side);
    const BitBoard them_occ = pos.bb(~side);

    BitBoard piece_bb = us_occ & pos.bb(PieceType::KNIGHT());

    while (piece_bb)
    {
        const Square   from    = Square::from_ordinal(piece_bb.pop_lsb());
        const BitBoard attacks = Attacks::knight_attacks(from) & (~us_occ);

        append_moves_from_sq_to_bb(movelist, from, attacks & (~them_occ), MoveFlag::NORMAL());
        append_moves_from_sq_to_bb(movelist, from, attacks & them_occ, MoveFlag::CAPTURE());
    }
}

void append_bishop_moves(MoveList& movelist, const PositionState& pos, const Color side) {
    const BitBoard us_occ   = pos.bb(side);
    const BitBoard them_occ = pos.bb(~side);

    BitBoard piece_bb = us_occ & pos.bb(PieceType::BISHOP());

    while (piece_bb)
    {
        const Square   from    = Square::from_ordinal(piece_bb.pop_lsb());
        const BitBoard attacks = Attacks::bishop_attacks(from, us_occ | them_occ) & (~us_occ);

        append_moves_from_sq_to_bb(movelist, from, attacks & (~them_occ), MoveFlag::NORMAL());
        append_moves_from_sq_to_bb(movelist, from, attacks & them_occ, MoveFlag::CAPTURE());
    }
}

void append_rook_moves(MoveList& movelist, const PositionState& pos, const Color side) {
    const BitBoard us_occ   = pos.bb(side);
    const BitBoard them_occ = pos.bb(~side);

    BitBoard piece_bb = us_occ & pos.bb(PieceType::ROOK());

    while (piece_bb)
    {
        const Square   from    = Square::from_ordinal(piece_bb.pop_lsb());
        const BitBoard attacks = Attacks::rook_attacks(from, us_occ | them_occ) & (~us_occ);

        append_moves_from_sq_to_bb(movelist, from, attacks & (~them_occ), MoveFlag::NORMAL());
        append_moves_from_sq_to_bb(movelist, from, attacks & them_occ, MoveFlag::CAPTURE());
    }
}

void append_queen_moves(MoveList& movelist, const PositionState& pos, const Color side) {
    const BitBoard us_occ   = pos.bb(side);
    const BitBoard them_occ = pos.bb(~side);

    BitBoard piece_bb = us_occ & pos.bb(PieceType::QUEEN());

    while (piece_bb)
    {
        const Square   from    = Square::from_ordinal(piece_bb.pop_lsb());
        const BitBoard attacks = Attacks::queen_attacks(from, us_occ | them_occ) & (~us_occ);

        append_moves_from_sq_to_bb(movelist, from, attacks & (~them_occ), MoveFlag::NORMAL());
        append_moves_from_sq_to_bb(movelist, from, attacks & them_occ, MoveFlag::CAPTURE());
    }
}

void append_king_moves(MoveList& movelist, const PositionState& pos, const Color side) {
    const BitBoard us_occ   = pos.bb(side);
    const BitBoard them_occ = pos.bb(~side);

    BitBoard piece_bb = us_occ & pos.bb(PieceType::KING());

    while (piece_bb)
    {
        const Square   from    = Square::from_ordinal(piece_bb.pop_lsb());
        const BitBoard attacks = Attacks::king_attacks(from) & (~us_occ);

        append_moves_from_sq_to_bb(movelist, from, attacks & (~them_occ), MoveFlag::NORMAL());
        append_moves_from_sq_to_bb(movelist, from, attacks & them_occ, MoveFlag::CAPTURE());
    }
}

}  // namespace

}
