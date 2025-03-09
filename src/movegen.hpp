#ifndef VOLTA_MOVEGEN_HPP__
#define VOLTA_MOVEGEN_HPP__

#include "move.hpp"
#include "position.hpp"
#include "utility.hpp"

namespace Volta::Chess {

using MoveList = Utility::fixed_vector<Move, 350>;

void append_all_moves(MoveList& movelist, const PositionState& pos);

}

#endif
