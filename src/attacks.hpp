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

        attacks[sq] |= shift(sq_bb, Direction::NORTH());
        attacks[sq] |= shift(sq_bb, Direction::SOUTH());
        attacks[sq] |= shift(sq_bb, Direction::EAST());
        attacks[sq] |= shift(sq_bb, Direction::WEST());
        attacks[sq] |= shift(sq_bb, Direction::NORTH_EAST());
        attacks[sq] |= shift(sq_bb, Direction::NORTH_WEST());
        attacks[sq] |= shift(sq_bb, Direction::SOUTH_EAST());
        attacks[sq] |= shift(sq_bb, Direction::SOUTH_WEST());
    }

    return attacks;
}

consteval std::array<BitBoard, Square::COUNT()> generate_knight_attacks() {
    std::array<BitBoard, Square::COUNT()> attacks{};

    for (std::size_t sq = 0; sq < Square::COUNT(); sq++)
    {
        const auto sq_bb = Square::from_ordinal(sq).to_bb();

        attacks[sq] |= shift(sq_bb, Direction::NORTH(), Direction::NORTH_EAST());
        attacks[sq] |= shift(sq_bb, Direction::NORTH(), Direction::NORTH_WEST());
        attacks[sq] |= shift(sq_bb, Direction::SOUTH(), Direction::SOUTH_EAST());
        attacks[sq] |= shift(sq_bb, Direction::SOUTH(), Direction::SOUTH_WEST());
        attacks[sq] |= shift(sq_bb, Direction::WEST(), Direction::NORTH_WEST());
        attacks[sq] |= shift(sq_bb, Direction::WEST(), Direction::SOUTH_WEST());
        attacks[sq] |= shift(sq_bb, Direction::EAST(), Direction::NORTH_EAST());
        attacks[sq] |= shift(sq_bb, Direction::EAST(), Direction::SOUTH_EAST());
    }

    return attacks;
}

constexpr BitBoard generate_mask_ray(const Square start, const Direction dir) {
    BitBoard attack{};
    BitBoard sq_bb   = start.to_bb();
    BitBoard next_bb = shift(sq_bb, dir);

    while ((sq_bb = next_bb))
    {
        next_bb = shift(sq_bb, dir);

        if (!next_bb)
            break;

        attack |= sq_bb;
    }

    return attack;
}

template<typename... DirectionType>
constexpr BitBoard generate_mask_rays(const Square start, const DirectionType... dir) {
    return (generate_mask_ray(start, dir) | ...);
}

constexpr BitBoard bishop_mask(const Square sq) {
    return generate_mask_rays(sq, Direction::NORTH_EAST(), Direction::NORTH_WEST(),
                              Direction::SOUTH_EAST(), Direction::SOUTH_WEST());
}

constexpr BitBoard rook_mask(const Square sq) {
    return generate_mask_rays(sq, Direction::NORTH(), Direction::SOUTH(), Direction::EAST(),
                              Direction::WEST());
}

consteval std::array<BitBoard, Square::COUNT()> generate_bishop_masks() {
    std::array<BitBoard, Square::COUNT()> attacks{};

    for (std::size_t sq_idx = 0; sq_idx < Square::COUNT(); sq_idx++)
        attacks[sq_idx] = bishop_mask(Square::from_ordinal(sq_idx));

    return attacks;
}

consteval std::array<BitBoard, Square::COUNT()> generate_rook_masks() {
    std::array<BitBoard, Square::COUNT()> attacks{};

    for (std::size_t sq_idx = 0; sq_idx < Square::COUNT(); sq_idx++)
        attacks[sq_idx] = rook_mask(Square::from_ordinal(sq_idx));

    return attacks;
}

constexpr BitBoard
generate_attack_ray(const BitBoard occ, const Square start, const Direction dir) {
    BitBoard attack{};
    BitBoard sq_bb = start.to_bb();

    while ((sq_bb = shift(sq_bb, dir)))
    {
        attack |= sq_bb;

        if (occ & sq_bb)
            break;
    }

    return attack;
}

template<typename... DirectionType>
constexpr BitBoard
generate_attack_rays(const BitBoard occ, const Square start, const DirectionType... dir) {
    return (generate_attack_ray(occ, start, dir) | ...);
}

constexpr BitBoard generate_bishop_attacks(Square sq, BitBoard occ) {
    return generate_attack_rays(occ, sq, Direction::NORTH_EAST(), Direction::NORTH_WEST(),
                                Direction::SOUTH_EAST(), Direction::SOUTH_WEST());
}

constexpr BitBoard generate_rook_attacks(Square sq, BitBoard occ) {
    return generate_attack_rays(occ, sq, Direction::NORTH(), Direction::SOUTH(), Direction::EAST(),
                                Direction::WEST());
}

struct MagicEntry {
    BitBoard     mask;
    std::int64_t magic;
    std::uint8_t shift;

    constexpr std::size_t get_index(BitBoard bb) {
        return static_cast<std::uint64_t>(
                 static_cast<std::int64_t>(static_cast<std::uint64_t>(bb & mask)) * magic)
            >> shift;
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
    static constexpr BitBoard pawn_attacks(BitBoard pawn_bb, Color side) {
        const Direction push_dir = side == Color::WHITE() ? Direction::NORTH() : Direction::SOUTH();
        return shift(pawn_bb, push_dir, Direction::EAST())
             | shift(pawn_bb, push_dir, Direction::WEST());
    }

    static constexpr BitBoard king_attacks(Square sq) { return KingAttacks[sq.ordinal()]; }

    static constexpr BitBoard knight_attacks(Square sq) { return KnightAttacks[sq.ordinal()]; }

    static constexpr BitBoard bishop_mask(Square sq) { return BishopMasks[sq.ordinal()]; }

    static BitBoard bishop_attacks(Square sq, BitBoard occ) {
        return BishopAttacks[sq.ordinal()][BishopMagics[sq.ordinal()].get_index(occ)];
    }

    static constexpr BitBoard rook_mask(Square sq) { return RookMasks[sq.ordinal()]; }

    static BitBoard rook_attacks(Square sq, BitBoard occ) {
        return RookAttacks[sq.ordinal()][RookMagics[sq.ordinal()].get_index(occ)];
    }

    static BitBoard queen_attacks(Square sq, BitBoard occ) {
        return bishop_attacks(sq, occ) | rook_attacks(sq, occ);
    }

    static void init_magics();
};

}

#endif
