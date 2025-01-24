#include <bit>
#include <iostream>
#include <limits>
#include <vector>

#include "magics.hpp"
#include "attacks.hpp"
#include "common.hpp"
#include "utility.hpp"

namespace Volta::Chess {

namespace {

constexpr std::vector<BitBoard> blocker_configurations(BitBoard mask) {
    std::vector<BitBoard> configurations(1 << mask.popcount());
    BitBoard              subset = 0;

    for (auto& configuration : configurations)
    {
        configuration = subset;
        subset        = (subset - mask) & mask;
    }

    return configurations;
}

constexpr std::vector<BitBoard>
bishop_attacks_under_blockers(Square sq, const std::vector<BitBoard>& blockers) {
    std::vector<BitBoard> attacks;
    attacks.reserve(blockers.size());

    for (const auto blocker : blockers)
        attacks.push_back(Detail::generate_bishop_attacks(sq, blocker));

    return attacks;
}

constexpr std::vector<BitBoard> rook_attacks_under_blockers(Square                       sq,
                                                            const std::vector<BitBoard>& blockers) {
    std::vector<BitBoard> attacks;
    attacks.reserve(blockers.size());

    for (const auto blocker : blockers)
        attacks.push_back(Detail::generate_rook_attacks(sq, blocker));

    return attacks;
}

}

bool test_magic(std::uint64_t                magic,
                std::uint8_t                 shift,
                const std::vector<BitBoard>& blockers,
                const std::vector<BitBoard>& attacks,
                Square                       sq) {
    std::vector<BitBoard> map(blockers.size(), 0ULL);

    for (std::size_t i = 0; i < blockers.size(); i++)
    {
        std::size_t idx = (magic * std::uint64_t(blockers[i])) >> shift;

        if (map[idx] != 0ULL && map[idx] != attacks[i])
            return false;

        map[idx] = attacks[i];
    }

    return true;
}

Detail::MagicEntry find_bishop_magic(Square sq) {
    Utility::PRNG rng{10000};

    const BitBoard              mask     = Attacks::bishop_mask(sq);
    const std::vector<BitBoard> blockers = blocker_configurations(mask);
    const std::vector<BitBoard> attacks  = bishop_attacks_under_blockers(sq, blockers);
    const std::uint8_t          shift    = Square::COUNT() - mask.popcount();

    assert(blockers.size() == attacks.size());

    while (true)
    {
        std::uint64_t magic_candidate = rng.sparse_rand();
        if (test_magic(magic_candidate, shift, blockers, attacks, sq))
            return {.mask = mask, .magic = magic_candidate, .shift = shift};
    }
}

Detail::MagicEntry find_rook_magic(Square sq) {
    Utility::PRNG rng{10000};

    const BitBoard        mask     = Attacks::rook_mask(sq);
    std::vector<BitBoard> blockers = blocker_configurations(mask);
    std::vector<BitBoard> attacks  = rook_attacks_under_blockers(sq, blockers);
    const std::uint8_t    shift    = Square::COUNT() - mask.popcount();

    assert(blockers.size() == attacks.size());

    while (true)
    {
        std::uint64_t magic_candidate = rng.sparse_rand();
        if (test_magic(magic_candidate, shift, blockers, attacks, sq))
            return {.mask = mask, .magic = magic_candidate, .shift = shift};
    }
}
}
