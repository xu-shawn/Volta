#include <bit>
#include <cstddef>
#include <iostream>
#include <limits>
#include <vector>

#include "bitboard.hpp"
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

template<typename Function>
constexpr std::vector<BitBoard> attacks_under_blockers(const Square                 sq,
                                                       const std::vector<BitBoard>& blockers,
                                                       Function&&                   attacks_fn) {
    std::vector<BitBoard> attacks;
    attacks.reserve(blockers.size());

    for (const auto blocker : blockers)
        attacks.push_back(std::forward<Function>(attacks_fn)(sq, blocker));

    return attacks;
}

constexpr bool test_magic(const std::uint64_t          magic,
                          const std::uint8_t           shift,
                          const std::vector<BitBoard>& blockers,
                          const std::vector<BitBoard>& attacks,
                          std::vector<std::size_t>&    generation,
                          std::vector<BitBoard>&       map,
                          const std::size_t            curr_generation,
                          const Square                 sq) {
    for (std::size_t i = 0; i < blockers.size(); i++)
    {
        const std::size_t idx = (magic * std::uint64_t(blockers[i])) >> shift;

        if (generation[idx] == curr_generation && map[idx] != 0ULL && map[idx] != attacks[i])
            return false;

        map[idx]        = attacks[i];
        generation[idx] = curr_generation;
    }

    return true;
}

template<typename F1, typename F2>
constexpr Detail::MagicEntry find_magic(const Square sq, F1&& mask_fn, F2&& attacks_fn) {
    Utility::PRNG rng{10000};

    const BitBoard     mask  = std::forward<F1>(mask_fn)(sq);
    const std::uint8_t shift = Square::COUNT() - mask.popcount();

    const std::vector<BitBoard> blockers = blocker_configurations(mask);
    const std::vector<BitBoard> attacks  = attacks_under_blockers(sq, blockers, attacks_fn);
    std::vector<std::size_t>    generation(blockers.size(), 0ULL);
    std::vector<BitBoard>       map(blockers.size(), 0ULL);

    assert(blockers.size() == attacks.size());

    for (std::size_t curr_generation = 1;; curr_generation++)
    {
        std::uint64_t magic_candidate = rng.sparse_rand();
        if (test_magic(magic_candidate, shift, blockers, attacks, generation, map, curr_generation,
                       sq))
            return {.mask = mask, .magic = magic_candidate, .shift = shift};
    }
}

}

constexpr Detail::MagicEntry find_bishop_magic(const Square sq) {
    return find_magic(sq, Attacks::bishop_mask, Detail::generate_bishop_attacks);
}

constexpr Detail::MagicEntry find_rook_magic(const Square sq) {
    return find_magic(sq, Attacks::rook_mask, Detail::generate_rook_attacks);
}

}
