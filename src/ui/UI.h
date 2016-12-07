#pragma once
#include "../backend/Control.h"
#include "../backend/Display.h"
#include "../core/GameState.h"

namespace ui {

struct UI {
    UI ();
    void process_control (Control ctrl);
    void render (disp::Display& disp);
    
private:
    game::GameState game_state;
};

}
