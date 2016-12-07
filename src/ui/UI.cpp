#include "UI.h"
#include "constants.h"

namespace ui {

UI::UI ()
{
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

    Tile fill_tile('.', Color::grey(0x003300), Color::black());
    for (int x = 0; x < viewport_width; x++) {
        for (int y = 0; y < viewport_height; y++) {
            g.render_tile(cx + x, cy + y, fill_tile);
        }
    }

    Tile player_tile('@', Color::black(), Color::white());
    g.render_tile(cx + game_state.player.x,
                  cy + game_state.player.y,
                  player_tile);
}


}
