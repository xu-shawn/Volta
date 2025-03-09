#include <iostream>
#include <string_view>

#include "attacks.hpp"
#include "position.hpp"
#include "movegen.hpp"

int main() {
    using namespace Volta::Chess;

    Attacks::init_magics();

    MoveList      movelist{};
    PositionState pos = PositionState::startpos();

    append_all_moves(movelist, pos, Color::WHITE());

    for (const Move move : movelist)
        std::cout << move.to_uci() << std::endl;

    for (const Move move : movelist)
    {
        PositionState newPos = pos;
        newPos.make_move(move);
        std::cout << newPos << std::endl;
    }
}
