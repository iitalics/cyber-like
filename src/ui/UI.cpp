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
    Tile fill_tile('.', Color::grey(1));
    for (int x = 0; x < viewport_width; x++) {
        for (int y = 0; y < viewport_height; y++) {
            g.render_tile(cx + x, cy + y, fill_tile);
        }
    }
    Tile wall_tile('#', Color::grey(1), Color::grey(2));
    enum { W = 20, H = 10 };
    for (int i = 0; i < W; i++)
        g.render_tile(cx + viewport_width - W + i,
                      cy + H,
                      wall_tile);
    for (int i = 0; i < H; i++)
        g.render_tile(cx + viewport_width - W,
                      cy + i,
                      wall_tile);

    /* player */
    Tile player_tile('@', Color::black(), Color::white());
    g.render_tile(cx + game_state.player.x,
                  cy + game_state.player.y,
                  player_tile);

    /* debug text */
    auto text = boost::format("control: %d") % game_state.last_ctrl;
    g.render_text(1, 1, text.str());
}


}
