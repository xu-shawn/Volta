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

    // std::cout << int(pos.stm().to_underlying()) << std::endl;

    // append_all_moves(movelist, pos);

    // for (const Move move : movelist)
    //     std::cout << move.to_uci() << std::endl;

    // for (const Move move : movelist)
    // {
    //     PositionState newPos = pos;
    //     newPos.make_move(move);
    //     std::cout << newPos << std::endl;
    // }

    // std::cout << perft(pos, 5) << std::endl;

    pos =
      PositionState::from_fen("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w - - 0 1");

    // Move move = move_from_uci(pos, "g2g1n");

    // pos.make_move(move);

    split_perft(pos, 5);
}
