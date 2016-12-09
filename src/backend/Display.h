#pragma once
#include <cstdint>
#include <memory>
#include "Color.h"
#include "TileSet.h"

namespace disp {

class Display {
public:
    virtual ~Display () = 0;

    /* interface */
    std::unique_ptr<TileSet> tile_set;
    virtual void render_tile (int x, int y, TileSet::id tile) = 0;
    virtual void begin_draw () = 0;
    virtual void end_draw () = 0;

    /* dimensions */
    inline int width () const { return width_; }
    inline int height () const { return height_; }

    /* singleton */
    static Display* instance () { return instance_.get(); }
    static void set_instance (Display* to);

    /* utility */
    void render_text (int x, int y, boost::string_ref text,
                      Color fg = Color::white(),
                      int wrap = -1);

protected:
    int width_, height_;
  
private:
    static std::unique_ptr<Display> instance_;
};


}
