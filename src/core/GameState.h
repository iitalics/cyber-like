#pragma once
#include "../util/geom.h"
#include "../backend/Control.h"
#include "Map.h"
#include "Entity.h"

namespace game {

struct GameState {
    GameState ();

    void process_control (Control ctrl);
    
    /* player */
    ivec player;
    
    /* scene */
    std::vector<std::unique_ptr<Entity>> scene;

    /* map */
    Map map;

    /* etc */
    Control last_ctrl;

    /* info about interacting entity; describes entity you're moving into */
    std::string interact_direction;
    std::string interact_desc;
};

}
