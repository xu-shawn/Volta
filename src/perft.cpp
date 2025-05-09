#include "perft.hpp"

#include <cstdint>

#include "movegen.hpp"

namespace Volta {

namespace Chess {

void split_perft(const PositionState& pos, std::int32_t depth) {
    MoveList moves;
    append_all_moves(moves, pos);

    for (const auto move : moves)
    {
        PositionState newPos = pos;
        newPos.make_move(move);

        if (!newPos.is_ok())
            continue;

        std::cout << move.to_uci() << " " << perft(newPos, depth - 1) << std::endl;
    }
}

std::uint64_t perft(const PositionState& pos, std::int32_t depth) {
    if (depth == 0)
        return 1;

    MoveList moves;
    append_all_moves(moves, pos);

    std::uint64_t counter = 0;

    for (const auto move : moves)
    {
        PositionState newPos = pos;
        newPos.make_move(move);

        if (!newPos.is_ok())
            continue;

        counter += perft(newPos, depth - 1);
    }

    return counter;
}

}

}
