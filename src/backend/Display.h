#pragma once
#include <cstdint>
#include <memory>
#include "Color.h"
#include "TileSet.h"

namespace disp {

/**
   Abstract class for backend display.
 */
class Display {
public:
    virtual ~Display () = 0;

    /**
       TileSet to find tiles or fonts from.
       @see TileSet
       @see render_tile
       @see render_text
     */
    std::unique_ptr<TileSet> tile_set;

    /**
       Render a tile somewhere on the screen
       @param x X coordinate.
       @param y Y coordinate.
       @param tile tile descriptor to draw.
       @see TileSet
    */
    virtual void render_tile (int x, int y, TileSet::id tile) = 0;

    /**
       Render text somewhere on the screen.
       Returns the X coordinate following the last rendered character.
       @param x X coordinate.
       @param y Y coordinate.
       @param text text to render.
       @param font name of font to render with.
       @param wrap maximum width of text before wrapping to next line (optional).
    */
    int render_text (int x, int y, boost::string_ref text,
                     boost::string_ref font,
                     int wrap = -1);

    /**
       Begin drawing routine.
       All render_XYZ calls should happen within begin_draw and end_draw.
       @see end_draw()
    */
    virtual void begin_draw () = 0;

    /**
       End drawing routine.
       All render_XYZ calls should happen within begin_draw and end_draw.
       @see begin_draw()
    */
    virtual void end_draw () = 0;


    /**
       Returns width of the display.
    */
    inline int width () const { return width_; }
    /**
       Returns height of the display.
    */
    inline int height () const { return height_; }

    /**
       Returns global instance of the used display.
       @see set_instance
    */
    static Display* instance () { return instance_.get(); }

    /**
       Change the global instance.
       @param to unowned pointer to display object to be the global instance.
       @see instance
     */
    static void set_instance (Display* to);

protected:
    int width_, height_;
  
private:
    static std::unique_ptr<Display> instance_;
};


}
