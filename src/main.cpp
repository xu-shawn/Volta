#include <iostream>
#include <string_view>

#include "attacks.hpp"
#include "bbmanip.hpp"
#include "bitboard.hpp"
#include "coordinates.hpp"
#include "piece.hpp"
#include "position.hpp"

int main() {
    using namespace Volta::Chess;
    using namespace std::string_view_literals;

    auto startpos =
      PositionState::from_fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"sv);

    for (const auto bb : Attacks::RookMasks)
    {
        std::cout << std::string(bb) << std::endl;
    }
}
