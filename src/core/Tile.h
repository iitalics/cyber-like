#pragma once
#include "../backend/Display.h"
#include <memory>
#include <string>

namespace game {

struct Tile {
    Tile (uint32_t chr,
          disp::Color fg, disp::Color bg,
          bool walkable = true);

    static Tile unwalkable ();
    
    /* appearance */
    uint32_t chr;
    disp::Color fg, bg;

    /* attributes */
    bool walkable;

    // ehh
    std::string desc_ptr;
    inline boost::string_ref description () const
    {
        return desc_ptr;
    }
    inline Tile& set_description (boost::string_ref r)
    {
        desc_ptr = r.to_string();
        return *this;
    }
};

}
