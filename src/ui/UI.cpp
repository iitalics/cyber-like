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

    /* viewport border */
    Tile border_tile(0x2550, Color::white());
    for (int x = 0; x < viewport_width; x++) {
        g.render_tile(cx + x, cy - 1, border_tile);
        g.render_tile(cx + x, cy + viewport_height, border_tile);
    }
    border_tile.chr = 0x2551;
    for (int y = 0; y < viewport_height; y++) {
        g.render_tile(cx - 1, cy + y, border_tile);
        g.render_tile(cx + viewport_width, cy + y, border_tile);
    }
    border_tile.chr = 0x2557;
    g.render_tile(cx + viewport_width, cy - 1, border_tile);
    border_tile.chr = 0x255a;
    g.render_tile(cx - 1, cy + viewport_height, border_tile);
    border_tile.chr = 0x255d;
    g.render_tile(cx + viewport_width, cy + viewport_height, border_tile);
    border_tile.chr = 0x2554;
    g.render_tile(cx - 1, cy - 1, border_tile);

    /* view */
    for (int x = 0; x < viewport_width; x++) {
        for (int y = 0; y < viewport_height; y++) {
            auto map_tile = game_state.map.tile_at(x, y);
            Tile fill_tile(map_tile.chr, map_tile.fg, map_tile.bg);
            g.render_tile(cx + x, cy + y, fill_tile);
        }
    }
    /* player */
    Tile player_tile('@', Color::black(), Color::white());
    g.render_tile(cx + game_state.player.x,
                  cy + game_state.player.y,
                  player_tile);
    auto tile_on = game_state.map.tile_at(game_state.player.x,
                                          game_state.player.y);
    g.render_text(cx + 1, cy + viewport_height + 1,
                  tile_on.description(),
                  Color::grey(2));
}


}
