#ifndef VOLTA_MAGICS_HPP__
#define VOLTA_MAGICS_HPP__

#include "attacks.hpp"
#include "bitboard.hpp"

namespace Volta::Chess {

Detail::MagicEntry find_bishop_magic(const Square sq);
Detail::MagicEntry find_rook_magic(const Square sq);

}

#endif
