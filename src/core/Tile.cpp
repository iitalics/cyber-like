#include "Tile.h"

namespace game {

Tile::Tile (disp::TileSet::id tid,
            bool w)
    : tile_id(tid)
    , walkable(w)
{}


}

