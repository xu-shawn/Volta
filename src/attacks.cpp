#include "attacks.hpp"

#include <array>
#include <format>
#include <iostream>

namespace Volta::Chess {

std::array<Detail::MagicEntry, Square::COUNT()>        Attacks::BishopMagics{};
std::array<std::array<BitBoard, 512>, Square::COUNT()> Attacks::BishopAttacks{};

std::array<Detail::MagicEntry, Square::COUNT()>         Attacks::RookMagics{};
std::array<std::array<BitBoard, 4096>, Square::COUNT()> Attacks::RookAttacks{};

void Attacks::init_magics() {
    std::cout << "{\n";
    for (std::size_t sq_idx = 0; sq_idx < Square::COUNT(); sq_idx++)
    {
        BishopMagics[sq_idx]       = find_bishop_magic(Square::from_ordinal(sq_idx));
        const BitBoard mask        = BishopMasks[sq_idx];
        BitBoard       curr_subset = 0ULL;
        std::cout << std::format("{:#018x}L,\n", std::uint64_t(BishopMagics[sq_idx].magic));

        for (std::size_t i = 0; i < 1 << mask.popcount(); i++)
        {
            BishopAttacks[sq_idx][BishopMagics[sq_idx].get_index(curr_subset)] =
              Detail::generate_bishop_attacks(Square::from_ordinal(sq_idx), curr_subset);
            curr_subset = (curr_subset - mask) & mask;
        }
    }
    std::cout << "}\n{\n";
    for (std::size_t sq_idx = 0; sq_idx < Square::COUNT(); sq_idx++)
    {
        RookMagics[sq_idx]         = find_rook_magic(Square::from_ordinal(sq_idx));
        const BitBoard mask        = RookMasks[sq_idx];
        BitBoard       curr_subset = 0;
        std::cout << std::format("{:#018x}L,\n", std::uint64_t(RookMagics[sq_idx].magic));

        for (std::size_t i = 0; i < 1 << mask.popcount(); i++)
        {
            RookAttacks[sq_idx][RookMagics[sq_idx].get_index(curr_subset)] =
              Detail::generate_rook_attacks(Square::from_ordinal(sq_idx), curr_subset);
            curr_subset = (curr_subset - mask) & mask;
        }
    }
    std::cout << "}";
}

}
