#include "movegen.hpp"

#include "attacks.hpp"
#include "bitboard.hpp"
#include "common.hpp"
#include "move.hpp"
#include "piece.hpp"

namespace Volta::Chess {

namespace {

void append_moves_from_sq_to_bb(MoveList&      movelist,
                                const Square   from,
                                BitBoard       bb,
                                const MoveFlag flag);

void append_pawn_moves(MoveList& movelist, const PositionState& pos);
void append_knight_moves(MoveList& movelist, const PositionState& pos);
void append_bishop_moves(MoveList& movelist, const PositionState& pos);
void append_rook_moves(MoveList& movelist, const PositionState& pos);
void append_queen_moves(MoveList& movelist, const PositionState& pos);
void append_king_moves(MoveList& movelist, const PositionState& pos);

}  // namespace

void append_all_moves(MoveList& movelist, const PositionState& pos) {
    append_pawn_moves(movelist, pos);
    append_knight_moves(movelist, pos);
    append_bishop_moves(movelist, pos);
    append_rook_moves(movelist, pos);
    append_queen_moves(movelist, pos);
    append_king_moves(movelist, pos);
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

void append_pawn_moves(MoveList& movelist, const PositionState& pos) {
    const Color    side     = pos.stm();
    const BitBoard us_occ   = pos.bb(side);
    const BitBoard them_occ = pos.bb(~side);
    const BitBoard occ      = us_occ | them_occ;

    const BitBoard pawn_bb        = pos.bb(PieceType::PAWN()) & us_occ;
    const BitBoard starting_rank  = side == Color::WHITE() ? Rank::RANK_2() : Rank::RANK_7();
    const BitBoard promotion_rank = side == Color::WHITE() ? Rank::RANK_8() : Rank::RANK_1();
    const BitBoard starting_pawns = pawn_bb & starting_rank;

    const Direction push_dir = side == Color::WHITE() ? Direction::NORTH() : Direction::SOUTH();

    {
        const BitBoard forward_push = shift(pawn_bb, push_dir) & ~occ;

        {
            BitBoard forward_push_normal = forward_push & ~promotion_rank;
            while (forward_push_normal)
            {
                const Square to = Square::from_ordinal(forward_push_normal.pop_lsb());
                movelist.push_back(Move(MoveFlag::NORMAL(), shift(to, push_dir.reverse()), to));
            }
        }

        {
            BitBoard forward_push_promotion = forward_push & promotion_rank;
            while (forward_push_promotion)
            {
                const Square to = Square::from_ordinal(forward_push_promotion.pop_lsb());

                movelist.push_back(Move(MoveFlag::make_promotion(PieceType::KNIGHT()),
                                        shift(to, push_dir.reverse()), to));
                movelist.push_back(Move(MoveFlag::make_promotion(PieceType::BISHOP()),
                                        shift(to, push_dir.reverse()), to));
                movelist.push_back(Move(MoveFlag::make_promotion(PieceType::ROOK()),
                                        shift(to, push_dir.reverse()), to));
                movelist.push_back(Move(MoveFlag::make_promotion(PieceType::QUEEN()),
                                        shift(to, push_dir.reverse()), to));
            }
        }
    }

    {
        BitBoard forward_double_push =
          shift(shift(pawn_bb & starting_rank, push_dir) & ~occ, push_dir) & ~occ;
        while (forward_double_push)
        {
            const Square to = Square::from_ordinal(forward_double_push.pop_lsb());
            movelist.push_back(
              Move(MoveFlag::NORMAL(), shift(to, push_dir.reverse(), push_dir.reverse()), to));
        }
    }

    {
        const BitBoard capture_west = shift(pawn_bb, push_dir, Direction::WEST())
                                    & (them_occ | pos.en_passant_destination().to_bb());

        {
            BitBoard capture_west_normal = capture_west & ~promotion_rank;
            while (capture_west_normal)
            {
                const Square to = Square::from_ordinal(capture_west_normal.pop_lsb());
                movelist.push_back(
                  Move(MoveFlag::CAPTURE(), shift(to, push_dir.reverse(), Direction::EAST()), to));
            }
        }

        {
            BitBoard capture_west_promotion = capture_west & promotion_rank;
            while (capture_west_promotion)
            {
                const Square to = Square::from_ordinal(capture_west_promotion.pop_lsb());

                movelist.push_back(Move(MoveFlag::make_promotion(PieceType::KNIGHT()),
                                        shift(to, push_dir.reverse(), Direction::EAST()), to));
                movelist.push_back(Move(MoveFlag::make_promotion(PieceType::BISHOP()),
                                        shift(to, push_dir.reverse(), Direction::EAST()), to));
                movelist.push_back(Move(MoveFlag::make_promotion(PieceType::ROOK()),
                                        shift(to, push_dir.reverse(), Direction::EAST()), to));
                movelist.push_back(Move(MoveFlag::make_promotion(PieceType::QUEEN()),
                                        shift(to, push_dir.reverse(), Direction::EAST()), to));
            }
        }
    }

    {
        const BitBoard capture_east = shift(pawn_bb, push_dir, Direction::EAST())
                                    & (them_occ | pos.en_passant_destination().to_bb());

        {
            BitBoard capture_east_normal = capture_east & ~promotion_rank;
            while (capture_east_normal)
            {
                const Square to = Square::from_ordinal(capture_east_normal.pop_lsb());
                movelist.push_back(
                  Move(MoveFlag::CAPTURE(), shift(to, push_dir.reverse(), Direction::WEST()), to));
            }
        }

        {
            BitBoard capture_east_promotion = capture_east & promotion_rank;
            while (capture_east_promotion)
            {
                const Square to = Square::from_ordinal(capture_east_promotion.pop_lsb());

                movelist.push_back(Move(MoveFlag::make_promotion(PieceType::KNIGHT()),
                                        shift(to, push_dir.reverse(), Direction::WEST()), to));
                movelist.push_back(Move(MoveFlag::make_promotion(PieceType::BISHOP()),
                                        shift(to, push_dir.reverse(), Direction::WEST()), to));
                movelist.push_back(Move(MoveFlag::make_promotion(PieceType::ROOK()),
                                        shift(to, push_dir.reverse(), Direction::WEST()), to));
                movelist.push_back(Move(MoveFlag::make_promotion(PieceType::QUEEN()),
                                        shift(to, push_dir.reverse(), Direction::WEST()), to));
            }
        }
    }
}

void append_knight_moves(MoveList& movelist, const PositionState& pos) {
    const Color    side     = pos.stm();
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

void append_bishop_moves(MoveList& movelist, const PositionState& pos) {
    const Color    side     = pos.stm();
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

void append_rook_moves(MoveList& movelist, const PositionState& pos) {
    const Color    side     = pos.stm();
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

void append_queen_moves(MoveList& movelist, const PositionState& pos) {
    const Color    side     = pos.stm();
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

void append_king_moves(MoveList& movelist, const PositionState& pos) {
    const Color    side     = pos.stm();
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
