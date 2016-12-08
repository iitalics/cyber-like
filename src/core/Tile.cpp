#include "Tile.h"

namespace game {


Tile::Tile (uint32_t c,
            disp::Color f, disp::Color b,
            bool w)
    : chr(c), fg(f), bg(b), walkable(w)
    , desc_ptr("")
{}

Tile Tile::unwalkable ()
{
    return Tile(' ',
                disp::Color::black(),
                disp::Color::black(),
                false);
}

}

