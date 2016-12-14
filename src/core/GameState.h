#pragma once
#include <lua5.1/lua.hpp>
#include "../util/geom.h"
#include "../backend/Action.h"
#include "Map.h"
#include "Entity.h"

namespace game {

struct GameState {
    GameState ();
    GameState (const GameState&) = delete;
    ~GameState ();
    
    void process_action (Action ac);

    /* lua */
    lua_State* lua;
    
    /* player */
    ivec player;
    
    /* scene */
    std::vector<std::unique_ptr<Entity>> scene;

    /* map */
    Map map;

    /* info about interacting entity; describes entity you're moving into */
    std::string interact_direction;
    std::string interact_desc;

    std::vector<std::string> debug_text;
};

}
