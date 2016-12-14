#pragma once
#include "../backend/Action.h"
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
       Process user input action.
       Delegates to either game_state or intermediate UI controls.
       @param ac the specified action.
    */
    void process_action (Action ac);

    /**
       Internal game state for current game.
    */
    game::GameState game_state;
};

}
