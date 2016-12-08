#include "Map.h"
#include <random>
#include <algorithm>
#include <chrono>

namespace game {

enum {
    KATA_A = 0x30a2,
    KATA_I = 0x30a4,
    KATA_U = 0x30a6,
    KATA_E = 0x30a8,
    KATA_O = 0x30aa,
};

Map::Map ()
{
    using namespace disp;
    
    /* dear lord */
    using HRClock = std::chrono::high_resolution_clock;
    std::default_random_engine rgen;
    rgen.seed(HRClock::now().time_since_epoch().count());

    tiles_ = {
        Tile(' ', Color::black(), Color::black(), 0), // 0
        Tile('-', Color::yellow(), Color::black()),   // 1
        Tile('.', Color::grey(1), Color::black()),    // 2
        Tile(',', Color::grey(1), Color::black()),    // 3
        Tile('+', Color::grey(2), Color::grey(1), 0), // 4
        Tile(' ', Color::grey(2), Color::grey(1), 0), // 5

        Tile('B', Color::red(), Color::rgb(0x000033)), // 6
        Tile('L', Color::red(), Color::rgb(0x000033)), // 7
        Tile('A', Color::red(), Color::rgb(0x000033)), // 8
        Tile('H', Color::red(), Color::rgb(0x000033)), // 9
        Tile(' ', Color::red(), Color::rgb(0x000033)), // 10

        Tile('D', Color::grey(3), Color::grey(1), 0), // 11
        Tile('o', Color::grey(3), Color::grey(0), 0), // 12
        Tile(' ', Color::black(), Color::black(), 1), // 13
    };

    tiles_[11].set_description("A door.");
    tiles_[12].set_description("A streetlight.");

    index_grid_.reserve(size * size);
    std::fill_n(std::back_inserter(index_grid_), size * size, 0);

    std::uniform_int_distribution<int> distr(2, 3);
    for (int y = 0; y < size; y++)
        for (int x = 0; x < size; x++) {
            index_grid_[x + y * size] =
                y < 16 ? distr(rgen) : 13;
        }

    for (int x = 0; x < size; x++) {
        if (x % 4 == 2)
            index_grid_[x + 20 * size] = 1;
        if (x % 9 == 3)
            index_grid_[x + 14 * size] = 12;
    }
    
    for (int x = 0; x < 20; x++)
        for (int y = 0; y < 10; y++) {
            int t = 5;
            if (x == 0 || y == 0 || x == 19 || y == 9)
                t = 4;
            index_grid_[(x + 24) + (y + 1) * size] = t;
        }

    index_grid_[31 + 9 * size] = 10;
    index_grid_[32 + 9 * size] = 6;
    index_grid_[33 + 9 * size] = 7;
    index_grid_[34 + 9 * size] = 8;
    index_grid_[35 + 9 * size] = 9;
    index_grid_[36 + 9 * size] = 10;

    index_grid_[33 + 10 * size] = 11;
    index_grid_[34 + 10 * size] = 11;
}

const Tile& Map::tile_at (int x, int y)
{
    if (x < 0 || y < 0
        || x >= size || y >= size)
        return tiles_[0];
    else
        return tiles_[index_grid_[x + y * size]];
}

}
