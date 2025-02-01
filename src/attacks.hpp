#ifndef VOLTA_ATTACKS_HPP__
#define VOLTA_ATTACKS_HPP__

#include <array>

#include "bbmanip.hpp"
#include "bitboard.hpp"
#include "common.hpp"
#include "coordinates.hpp"
#include "magics.hpp"

namespace Volta::Chess {

namespace Detail {

consteval std::array<BitBoard, Square::COUNT()> generate_king_attacks() {
    std::array<BitBoard, Square::COUNT()> attacks{};

    for (std::size_t sq = 0; sq < Square::COUNT(); sq++)
    {
        const auto sq_bb = Square::from_ordinal(sq).to_bb();

        attacks[sq] |= shift<Direction::NORTH()>(sq_bb);
        attacks[sq] |= shift<Direction::SOUTH()>(sq_bb);
        attacks[sq] |= shift<Direction::EAST()>(sq_bb);
        attacks[sq] |= shift<Direction::WEST()>(sq_bb);
        attacks[sq] |= shift<Direction::NORTH_EAST()>(sq_bb);
        attacks[sq] |= shift<Direction::NORTH_WEST()>(sq_bb);
        attacks[sq] |= shift<Direction::SOUTH_EAST()>(sq_bb);
        attacks[sq] |= shift<Direction::SOUTH_WEST()>(sq_bb);
    }

    return attacks;
}

consteval std::array<BitBoard, Square::COUNT()> generate_knight_attacks() {
    std::array<BitBoard, Square::COUNT()> attacks{};

    for (std::size_t sq = 0; sq < Square::COUNT(); sq++)
    {
        const auto sq_bb = Square::from_ordinal(sq).to_bb();

        attacks[sq] |= shift<Direction::NORTH_EAST()>(shift<Direction::NORTH()>(sq_bb));
        attacks[sq] |= shift<Direction::NORTH_WEST()>(shift<Direction::NORTH()>(sq_bb));

        attacks[sq] |= shift<Direction::SOUTH_EAST()>(shift<Direction::SOUTH()>(sq_bb));
        attacks[sq] |= shift<Direction::SOUTH_WEST()>(shift<Direction::SOUTH()>(sq_bb));

        attacks[sq] |= shift<Direction::NORTH_WEST()>(shift<Direction::WEST()>(sq_bb));
        attacks[sq] |= shift<Direction::SOUTH_WEST()>(shift<Direction::WEST()>(sq_bb));

        attacks[sq] |= shift<Direction::NORTH_EAST()>(shift<Direction::EAST()>(sq_bb));
        attacks[sq] |= shift<Direction::SOUTH_EAST()>(shift<Direction::EAST()>(sq_bb));
    }

    return attacks;
}

consteval std::array<BitBoard, Square::COUNT()> generate_bishop_masks() {
    std::array<BitBoard, Square::COUNT()> attacks{};

    for (std::size_t sq_idx = 0; sq_idx < Square::COUNT(); sq_idx++)
    {
        const Square sq    = Square::from_ordinal(sq_idx);
        BitBoard     sq_bb = sq.to_bb();

        while (sq_bb)
        {
            if (shift<Direction::NORTH_WEST()>(sq_bb) == 0)
                break;

            attacks[sq_idx] |= sq_bb;
            sq_bb = shift<Direction::NORTH_WEST()>(sq_bb);
        }

        sq_bb = sq.to_bb();
        while (sq_bb)
        {
            if (shift<Direction::NORTH_EAST()>(sq_bb) == 0)
                break;

            attacks[sq_idx] |= sq_bb;
            sq_bb = shift<Direction::NORTH_EAST()>(sq_bb);
        }

        sq_bb = sq.to_bb();
        while (sq_bb)
        {
            if (shift<Direction::SOUTH_WEST()>(sq_bb) == 0)
                break;

            attacks[sq_idx] |= sq_bb;
            sq_bb = shift<Direction::SOUTH_WEST()>(sq_bb);
        }

        sq_bb = sq.to_bb();
        while (sq_bb)
        {
            if (shift<Direction::SOUTH_EAST()>(sq_bb) == 0)
                break;

            attacks[sq_idx] |= sq_bb;
            sq_bb = shift<Direction::SOUTH_EAST()>(sq_bb);
        }

        attacks[sq_idx] &= (~sq.to_bb());
    }

    return attacks;
}

consteval std::array<BitBoard, Square::COUNT()> generate_rook_masks() {
    std::array<BitBoard, Square::COUNT()> attacks{};

    for (std::size_t sq_idx = 0; sq_idx < Square::COUNT(); sq_idx++)
    {
        const Square sq    = Square::from_ordinal(sq_idx);
        BitBoard     sq_bb = sq.to_bb();

        while (sq_bb)
        {
            if (shift<Direction::NORTH()>(sq_bb) == 0)
                break;

            attacks[sq_idx] |= sq_bb;
            sq_bb = shift<Direction::NORTH()>(sq_bb);
        }

        sq_bb = sq.to_bb();
        while (sq_bb)
        {
            if (shift<Direction::SOUTH()>(sq_bb) == 0)
                break;

            attacks[sq_idx] |= sq_bb;
            sq_bb = shift<Direction::SOUTH()>(sq_bb);
        }

        sq_bb = sq.to_bb();
        while (sq_bb)
        {
            if (shift<Direction::WEST()>(sq_bb) == 0)
                break;

            attacks[sq_idx] |= sq_bb;
            sq_bb = shift<Direction::WEST()>(sq_bb);
        }

        sq_bb = sq.to_bb();
        while (sq_bb)
        {
            if (shift<Direction::EAST()>(sq_bb) == 0)
                break;

            attacks[sq_idx] |= sq_bb;
            sq_bb = shift<Direction::EAST()>(sq_bb);
        }

        attacks[sq_idx] &= (~sq.to_bb());
    }

    return attacks;
}

constexpr BitBoard generate_bishop_attacks(Square sq, BitBoard occ) {
    BitBoard sq_bb   = sq.to_bb();
    BitBoard attacks = 0;

    while (sq_bb)
    {
        attacks |= sq_bb;
        if (occ & sq_bb)
            break;
        sq_bb = shift<Direction::NORTH_WEST()>(sq_bb);
    }

    sq_bb = sq.to_bb();
    while (sq_bb)
    {
        attacks |= sq_bb;
        if (occ & sq_bb)
            break;
        sq_bb = shift<Direction::NORTH_EAST()>(sq_bb);
    }

    sq_bb = sq.to_bb();
    while (sq_bb)
    {
        attacks |= sq_bb;
        if (occ & sq_bb)
            break;
        sq_bb = shift<Direction::SOUTH_WEST()>(sq_bb);
    }

    sq_bb = sq.to_bb();
    while (sq_bb)
    {
        attacks |= sq_bb;
        if (occ & sq_bb)
            break;
        sq_bb = shift<Direction::SOUTH_EAST()>(sq_bb);
    }

    attacks &= (~sq.to_bb());

    return attacks;
}

constexpr BitBoard generate_rook_attacks(Square sq, BitBoard occ) {
    BitBoard sq_bb   = sq.to_bb();
    BitBoard attacks = 0;

    while (sq_bb)
    {
        attacks |= sq_bb;
        if (occ & sq_bb)
            break;
        sq_bb = shift<Direction::NORTH()>(sq_bb);
    }

    sq_bb = sq.to_bb();
    while (sq_bb)
    {
        attacks |= sq_bb;
        if (occ & sq_bb)
            break;
        sq_bb = shift<Direction::SOUTH()>(sq_bb);
    }

    sq_bb = sq.to_bb();
    while (sq_bb)
    {
        attacks |= sq_bb;
        if (occ & sq_bb)
            break;
        sq_bb = shift<Direction::WEST()>(sq_bb);
    }

    sq_bb = sq.to_bb();
    while (sq_bb)
    {
        attacks |= sq_bb;
        if (occ & sq_bb)
            break;
        sq_bb = shift<Direction::EAST()>(sq_bb);
    }

    attacks &= (~sq.to_bb());

    return attacks;
}

struct MagicEntry {
    BitBoard      mask;
    std::uint64_t magic;
    std::uint8_t  shift;

    std::size_t get_index(BitBoard bb) {
        return (static_cast<std::uint64_t>(bb & mask) * magic) >> shift;
    }
};

}

class Attacks {
   private:
    static constexpr std::array<BitBoard, Square::COUNT()> KingAttacks =
      Detail::generate_king_attacks();
    static constexpr std::array<BitBoard, Square::COUNT()> KnightAttacks =
      Detail::generate_knight_attacks();

    static constexpr std::array<BitBoard, Square::COUNT()> BishopMasks =
      Detail::generate_bishop_masks();
    static std::array<Detail::MagicEntry, Square::COUNT()>        BishopMagics;
    static std::array<std::array<BitBoard, 512>, Square::COUNT()> BishopAttacks;

    static constexpr std::array<BitBoard, Square::COUNT()> RookMasks =
      Detail::generate_rook_masks();
    static std::array<Detail::MagicEntry, Square::COUNT()>         RookMagics;
    static std::array<std::array<BitBoard, 4096>, Square::COUNT()> RookAttacks;

   public:
    static constexpr BitBoard king_attacks(Square sq) { return KingAttacks[sq.ordinal()]; }

    static constexpr BitBoard knight_attacks(Square sq) { return KnightAttacks[sq.ordinal()]; }

    static constexpr BitBoard bishop_mask(Square sq) { return BishopMasks[sq.ordinal()]; }

    static constexpr BitBoard bishop_attacks(Square sq, BitBoard occ) {
        return BishopAttacks[sq.ordinal()][BishopMagics[sq.ordinal()].get_index(occ)];
    }

    static constexpr BitBoard rook_mask(Square sq) { return RookMasks[sq.ordinal()]; }

    static constexpr BitBoard rook_attacks(Square sq, BitBoard occ) {
        return RookAttacks[sq.ordinal()][RookMagics[sq.ordinal()].get_index(occ)];
    }

    static void init_magics();
};

}

#endif
