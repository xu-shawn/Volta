#ifndef VOLTA_MAGICS_HPP__
#define VOLTA_MAGICS_HPP__

#include "attacks.hpp"
#include "bitboard.hpp"

namespace Volta::Chess {

bool test_magic(std::uint64_t                magic,
                std::uint8_t                 shift,
                const std::vector<BitBoard>& blockers,
                const std::vector<BitBoard>& attacks,
                Square                       sq);

Detail::MagicEntry find_bishop_magic(Square sq);
Detail::MagicEntry find_rook_magic(Square sq);

}

#endif
