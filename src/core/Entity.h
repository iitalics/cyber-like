#pragma once
#include "../util/geom.h"
#include "../backend/Display.h"

namespace game {

struct Entity {
    Entity (disp::TileSet::id ap,
            lvec pos,
            bool walk=false);

    disp::TileSet::id appearance;
    lvec pos;
    bool walkable;
    std::string description;

    inline Entity& set_description (std::string d)
    {
        description = std::move(d);
        return *this;
    }
};

}
