#include <iostream>
#include <string_view>

#include "attacks.hpp"
#include "perft.hpp"
#include "piece.hpp"
#include "position.hpp"
#include "movegen.hpp"
#include "uci.hpp"

int main() {
    using namespace Volta::Chess;
    using namespace Volta::Engine;

    Attacks::init_magics();

    MoveList      movelist{};
    PositionState pos = PositionState::startpos();

    std::cout << int(pos.stm().to_underlying()) << std::endl;

    append_all_moves(movelist, pos);

    for (const Move move : movelist)
        std::cout << move.to_uci() << std::endl;

    for (const Move move : movelist)
    {
        PositionState newPos = pos;
        newPos.make_move(move);
        std::cout << newPos << std::endl;
    }

    std::cout << perft(pos, 5) << std::endl;

    // pos = PositionState::from_fen("rnbqkbnr/2pppppp/p7/Pp6/8/8/1PPPPPPP/RNBQKBNR w KQkq b6 0 3");

    // Move move = move_from_uci(pos, "a5b6");

    // pos.make_move(move);

    split_perft(pos, 6);
}
