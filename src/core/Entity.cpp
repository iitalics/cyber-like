#include "Entity.h"

namespace game {

Entity::Entity (disp::TileSet::id ap,
                lvec p,
                bool walk)
    : appearance(ap)
    , pos(p)
    , walkable(walk)
    , description("")
{}

}
