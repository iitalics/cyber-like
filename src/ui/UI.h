#pragma once
#include "../backend/Control.h"
#include "../backend/Display.h"
#include "../core/GameState.h"

namespace ui {

/**
   User interface class.
   Responsible for rendering the game, as well as managing the game state (delegating actions to it).
 */
struct UI {
    /**
       Default constructor for UI.
    */
    UI ();

    /**
       Render the game.
       @param disp display instance to render with.
    */
    void render (disp::Display& disp);

    /**
       Process user input control.
       Delegates ctrl appropriately.
       @param ctrl the kind of user input
    */
    void process_control (Control ctrl);

    /**
       Internal game state for current game.
    */
    game::GameState game_state;
};

}
