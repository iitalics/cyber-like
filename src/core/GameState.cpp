#include "GameState.h"

namespace game {

GameState::GameState ()
    : player(0, 0)
    , last_ctrl(0)
{}

void GameState::process_control (Control k)
{
    last_ctrl = k;

    if (k == ControlCode::left)
        player.x--;
    if (k == ControlCode::right)
        player.x++;
    if (k == ControlCode::up)
        player.y--;
    if (k == ControlCode::down)
        player.y++;
}

}
