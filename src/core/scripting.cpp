#include "scripting.h"

namespace game {

void setup_lua_environment (GameState& game_state)
{
    auto L = game_state.lua = lua_open();
    luaL_openlibs(L);
    game_state.debug_text.push_back("loaded lua");
}

}
