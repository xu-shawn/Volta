#ifndef VOLTA_MAGICS_HPP__
#define VOLTA_MAGICS_HPP__

namespace Volta::Chess {

namespace Detail {

struct MagicEntry;

}

Detail::MagicEntry find_bishop_magic(const Square sq);
Detail::MagicEntry find_rook_magic(const Square sq);

}

#endif
