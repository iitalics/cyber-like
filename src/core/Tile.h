#pragma once
#include "../backend/Display.h"
#include <memory>
#include <string>

namespace game {

struct Tile {
    explicit Tile (disp::TileSet::id tile_id,
                   bool walkable = true);
    
    /* appearance */
    disp::TileSet::id tile_id;

    /* attributes */
    bool walkable;
};

}
