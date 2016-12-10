#pragma once
#include "Color.h"
#include <boost/utility/string_ref.hpp>

namespace disp {

struct TileSet {
    using id = int;
    enum { missing_id = -1 };
    
    TileSet ();
    virtual ~TileSet () = 0;

    virtual void load_from_directory (boost::string_ref path) = 0;
    virtual id tile_by_name (boost::string_ref name) = 0;
};

}
