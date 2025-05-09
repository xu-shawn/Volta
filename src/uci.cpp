#include "uci.hpp"

#include "movegen.hpp"

namespace Volta {

namespace Engine {

Move move_from_uci(const PositionState& pos, std::string_view token) {
    MoveList moves;
    append_all_moves(moves, pos);

    for (const Move move : moves)
    {
        if (move.to_uci() == token)
        {
            return move;
        }
    }

    return Move::NONE();
}

}

}
