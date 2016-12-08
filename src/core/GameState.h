#pragma once
#include "../util/geom.h"
#include "../backend/Control.h"
#include "Map.h"

namespace game {

struct GameState {
    GameState ();

    void process_control (Control ctrl);
    
    /* player */
    ivec player;
    
    /* scene */

    /* map */
    Map map;

    /* items */

    /* etc */
    Control last_ctrl;
    std::string status_text;
};

}
