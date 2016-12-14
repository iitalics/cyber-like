#include "scripting.h"

namespace {
using namespace game;

GameState& lua_game_state (lua_State* L)
{
    lua_getglobal(L, "game_state_ref");
    GameState* ptr = (GameState*) lua_touserdata(L, -1);
    lua_pop(L, 1);
    return *ptr;
}

int lua_debug_print (lua_State* L)
{
    std::string out_str;
    {
        size_t len;
        auto chrs = luaL_checklstring(L, 1, &len);
        out_str = "[lua] ";
        out_str.append(chrs, len);
    }
    auto& game_state = lua_game_state(L);
    game_state.debug_text.push_back(std::move(out_str));
    return 0;
}

}



namespace game {

void setup_lua_environment (GameState& game_state)
{
    auto L = game_state.lua = lua_open();
    luaL_openlibs(L);

    lua_pushlightuserdata(L, &game_state);
    lua_setglobal(L, "game_state_ref");

    lua_pushcfunction(L, lua_debug_print);
    lua_setglobal(L, "print");

    if (luaL_dofile(L, "./lua/init.lua") != 0) {
        std::string out_str = "(lua) error: ";
        out_str.append(lua_tostring(L, -1));
        game_state.debug_text.push_back(out_str);
    }
}

}
