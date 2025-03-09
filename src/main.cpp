#include <iostream>
#include <string_view>

#include "attacks.hpp"
#include "perft.hpp"
#include "piece.hpp"
#include "position.hpp"
#include "movegen.hpp"

int main() {
    using namespace Volta::Chess;

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

    std::cout << perft(pos, 2) << std::endl;
    std::cout << perft(pos, 3) << std::endl;
    std::cout << perft(pos, 4) << std::endl;
    std::cout << perft(pos, 5) << std::endl;

    pos = PositionState::from_fen("rnbqkbnr/1ppppppp/p7/1B6/4P3/8/PPPP1PPP/RNBQK1NR b KQkq - 1 2");

    split_perft(pos, 1);
}
