#ifndef VOLTA_UCI_HPP__
#define VOLTA_UCI_HPP__

#include "move.hpp"
#include "position.hpp"

namespace Volta {

namespace Engine {

using namespace Chess;

Move move_from_uci(const PositionState& pos, std::string_view token);

}

}

#endif
