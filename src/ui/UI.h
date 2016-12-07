#pragma once
#include "../core/Game.h"
#include "../backend/Display.h"

namespace ui {

struct UI {
    UI (game::GameState& gs);
    void render (disp::Display& disp);

private:
    game::GameState& game_state;
};

}
