#include "GameState.h"
#include <boost/format.hpp>
#include <utf8.h>

namespace game {

GameState::GameState ()
    : player(0, 0)
    , last_ctrl(0)
{
    auto* ts = disp::Display::instance()->tile_set.get();
    map.generate_scene(ts);

    Entity light_proto(ts->tile_by_name("&lamp-1"),
                       lvec(5, 15));
    light_proto.set_description("A streetlight.");

    for (int i = 0; i < 6; i++) {
        scene.emplace_back(new Entity(light_proto));
        light_proto.pos.x += 8;
    }

    Entity cash_proto(ts->tile_by_name("&cash"),
                      lvec(3, 3),
                      true);
    cash_proto.set_description(u8"\u00a5"/*yen*/ "100.");
    scene.emplace_back(new Entity(std::move(cash_proto)));
}

void GameState::process_control (Control k)
{
    last_ctrl = k;

    boost::string_ref direction_string;
    auto player_dest = player;

    switch (k.code) {
    case ControlCode::left:
        player_dest += ivec::left();
        direction_string = "west";
        break;
    case ControlCode::right:
        player_dest += ivec::right();
        direction_string = "east";
        break;
    case ControlCode::up:
        player_dest += ivec::up();
        direction_string = "north";
        break;
    case ControlCode::down:
        player_dest += ivec::down();
        direction_string = "south";
        break;
    default:
        break;
    }

    if (player_dest != player) {
        /* reset interact text */
        interact_direction.clear();
        interact_desc.clear();

        /* find tile & entity at location */
        auto& dest_tile = map.tile_at(player_dest.x, player_dest.y);
        auto ent_it = std::find_if(scene.begin(), scene.end(),
                                   [&] (auto& ent) { return ent->pos == lvec(player_dest); });

        /* collide with entity */
        bool can_walk = true;
        if (ent_it != scene.end()) {
            auto* ent = (*ent_it).get();

            interact_desc = ent->description;
            if (ent->walkable) {
                interact_direction = "here";
            }
            else {
                interact_direction = direction_string.to_string();
                can_walk = false;
            }
        }

        /* collide with tile */
        if (can_walk && !dest_tile.walkable) {
            can_walk = false;
        }

        /* advance player */
        if (can_walk) {
            player = player_dest;
        }
    }
}

}
