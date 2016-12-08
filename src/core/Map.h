#include "Tile.h"
#include <vector>

namespace game {

struct Map {
    Map ();

    const Tile& tile_at (int x, int y);

private:
    enum { size = 60 };
    std::vector<Tile> tiles_;
    std::vector<int> index_grid_;
};

}
