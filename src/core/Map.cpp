#include "Map.h"
#include <random>
#include <algorithm>
#include <chrono>

namespace game {

using namespace disp;    


Map::Map ()
    : back_tile_(TileSet::missing_id, false)
{
    auto* ts = Display::instance()->tile_set.get();

    /* random seed using clock */
    std::default_random_engine rgen;
    rgen.seed(std::chrono::high_resolution_clock::now()
              .time_since_epoch().count());

    /* background */
    grid_.reserve(size * size);
    std::fill_n(std::back_inserter(grid_), size * size,
                back_tile_);

    /* generate the ground */
    std::uniform_int_distribution<int> distr(0, 1);
    auto pave_tile = [&] () {
        return Tile((distr(rgen) == 0
                     ? ts->tile_by_name("pave-1")
                     : ts->tile_by_name("pave-2")));
    };
    Tile street_tile(ts->tile_by_name("none"));

    for (int y = 0; y < size; y++)
        for (int x = 0; x < size; x++) {
            grid_[x + y * size] = size < 16 ? pave_tile() : street_tile;
        }

    /* lamps and road markings */
    Tile lamp(ts->tile_by_name("lamp-1"), false);
    lamp.description = "A streetlight.";
    for (int x = 0; x < size; x++) {
        if (x % 4 == 2)
            grid_[x + 20 * size] = Tile(ts->tile_by_name("road-mark-1"));
        if (x % 9 == 3)
            grid_[x + 14 * size] = lamp;
    }

    /* a building */
    Tile stone_wall_1(ts->tile_by_name("stone-wall-1"), false);
    Tile stone_wall_2(ts->tile_by_name("stone-wall-2"), false);
    for (int x = 0; x < 20; x++)
        for (int y = 0; y < 10; y++) {
            Tile& t = (x == 0 || y == 0 || x == 19 || y == 9)
                ? stone_wall_1
                : stone_wall_2;

            grid_[(x + 24) + (y + 1) * size] = t;
        }

    /* a sign & a door */
    grid_[31 + 9 * size] = Tile(ts->tile_by_name("sign-1"));
    grid_[32 + 9 * size] = Tile(ts->tile_by_name("sign-1-A"));
    grid_[33 + 9 * size] = Tile(ts->tile_by_name("sign-1-B"));
    grid_[34 + 9 * size] = Tile(ts->tile_by_name("sign-1-C"));
    grid_[35 + 9 * size] = Tile(ts->tile_by_name("sign-1-D"));
    grid_[36 + 9 * size] = Tile(ts->tile_by_name("sign-1"));
   
    Tile door(ts->tile_by_name("door-1"), false);
    door.description = "A door.";
    grid_[33 + 10 * size] =
        grid_[34 + 10 * size] = door;
}

const Tile& Map::tile_at (int x, int y)
{
    if (x < 0 || y < 0
        || x >= size || y >= size) {
        return back_tile_;
    }
    else
        return grid_[x + y * size];
}

}