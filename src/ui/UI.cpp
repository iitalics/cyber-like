#include "UI.h"
#include "constants.h"
#include <sstream>
#include <boost/format.hpp>

namespace ui {

UI::UI ()
{
}

void UI::process_control (Control ctrl)
{
    game_state.process_control(ctrl);
}

void UI::render (disp::Display& g)
{
    using namespace disp;

    int cx = (g.width() - viewport_width) / 2;
    int cy = (g.height() - viewport_height) / 2;

    auto* ts = g.tile_set.get();
    
    /* viewport border */
    //   a hhh b
    //   v     v
    //   v     v
    //   c hhh d
    auto tile_h = ts->tile_by_name("ui-vp-h");
    for (int x = 0; x < viewport_width; x++) {
        g.render_tile(cx + x, cy - 1, tile_h);
        g.render_tile(cx + x, cy + viewport_height, tile_h);
    }
    auto tile_v = ts->tile_by_name("ui-vp-v");
    for (int y = 0; y < viewport_height; y++) {
        g.render_tile(cx - 1, cy + y, tile_v);
        g.render_tile(cx + viewport_width, cy + y, tile_v);
    }
    g.render_tile(cx - 1, cy - 1,
                  ts->tile_by_name("ui-vp-a"));
    g.render_tile(cx + viewport_width, cy - 1,
                  ts->tile_by_name("ui-vp-b"));
    g.render_tile(cx - 1, cy + viewport_height,
                  ts->tile_by_name("ui-vp-c"));
    g.render_tile(cx + viewport_width, cy + viewport_height,
                  ts->tile_by_name("ui-vp-d"));

    /* view: map */
    for (int x = 0; x < viewport_width; x++) {
        for (int y = 0; y < viewport_height; y++) {
            auto map_tile = game_state.map.tile_at(x, y);
            g.render_tile(cx + x, cy + y, map_tile.tile_id);
        }
    }
    for (auto& ent : game_state.scene) {
        g.render_tile(cx + ent->pos.x,
                      cy + ent->pos.y,
                      ent->appearance);
    }

    /* player */
    g.render_tile(cx + game_state.player.x,
                  cy + game_state.player.y,
                  ts->tile_by_name("@player"));

    if (!game_state.interact_desc.empty()) {
        int tx = cx + 1;
        int ty = cy + viewport_height + 1;
        tx = g.render_text(tx, ty, "[", "ui-direction-font");
        tx = g.render_text(tx, ty, game_state.interact_direction,
                           "ui-direction-font");
        tx = g.render_text(tx, ty, "] ", "ui-direction-font");
        tx = g.render_text(tx, ty, game_state.interact_desc,
                           "ui-desc-font");
    }
}


}
