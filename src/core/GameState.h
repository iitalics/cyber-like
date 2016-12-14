#pragma once
#include "../util/geom.h"
#include "../backend/Action.h"
#include "Map.h"
#include "Entity.h"

namespace game {

struct GameState {
    GameState ();

    void process_action (Action ac);

    /* player */
    ivec player;
    
    /* scene */
    std::vector<std::unique_ptr<Entity>> scene;

    /* map */
    Map map;

    /* info about interacting entity; describes entity you're moving into */
    std::string interact_direction;
    std::string interact_desc;
};

}
