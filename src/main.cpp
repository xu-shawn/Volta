#include <iostream>
#include <string_view>

#include "attacks.hpp"
#include "bbmanip.hpp"
#include "bitboard.hpp"
#include "coordinates.hpp"
#include "magics.hpp"
#include "piece.hpp"
#include "position.hpp"

int main() {
    using namespace Volta::Chess;
    using namespace std::string_view_literals;

    for (std::uint8_t sq_idx = 0; sq_idx < 64; sq_idx++)
        std::cout << "Bishop Magic: Square " << std::string(Square::from_ordinal(sq_idx)) << ": "
                  << find_bishop_magic(Square::from_ordinal(sq_idx)).magic << std::endl;

    for (std::uint8_t sq_idx = 0; sq_idx < 64; sq_idx++)
        std::cout << "Rook Magic: Square " << std::string(Square::from_ordinal(sq_idx)) << ": "
                  << find_rook_magic(Square::from_ordinal(sq_idx)).magic << std::endl;
}
