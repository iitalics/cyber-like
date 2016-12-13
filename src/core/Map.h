#include "Tile.h"
#include <vector>

namespace game {

struct Map {
    Map ();

    void generate_scene (disp::TileSet* ts);
    
    Tile& tile_at (int x, int y);

private:
    enum { size = 60 };
    std::vector<Tile> grid_;
    Tile back_tile_;
};

}
