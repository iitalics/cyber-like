#pragma once
#include <vector>
#include <stdexcept>
#include <boost/optional.hpp>
#include "../Display.h"
#include "../Action.h"

#include <termbox.h>

namespace term {

struct TermCell {
    uint32_t chr;
    disp::Color fg, bg;
    bool transparent;
};

struct TermDisplay : public disp::Display {
    TermDisplay ();
    virtual ~TermDisplay ();

    virtual void render_tile (int x, int y, disp::TileSet::id tile);
    virtual void begin_draw ();
    virtual void end_draw ();

    boost::optional<Action> poll_user_action ();
    static uint16_t conv_color (disp::Color col);
private:
    std::vector<TermCell> tiles;
};

}
