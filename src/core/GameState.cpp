#include "GameState.h"

namespace game {

GameState::GameState ()
    : player(0, 0)
    , last_ctrl(0)
    , status_text("")
{}

void GameState::process_control (Control k)
{
    last_ctrl = k;

    auto player_dest = player;
    switch (k.code) {
    case ControlCode::left:
        player_dest += ivec::left();
        break;
    case ControlCode::right:
        player_dest += ivec::right();
        break;
    case ControlCode::up:
        player_dest += ivec::up();
        break;
    case ControlCode::down:
        player_dest += ivec::down();
        break;
    default:
        break;
    }

    if (player_dest != player) {
        auto& dest_tile = map.tile_at(player_dest.x, player_dest.y);
        status_text = dest_tile.description;

        if (dest_tile.walkable)
            player = player_dest;
    }
}

}
