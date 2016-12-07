#include "Display.h"
#include <utf8.h>

namespace disp {

std::unique_ptr<Display> Display::instance_ = nullptr;

Display::~Display () {}

void Display::set_instance (Display* d)
{
    instance_.reset(d);
}

void Display::render_text (int x, int y, boost::string_ref text, Color fg, int wrap)
{
    Tile tile(0, fg);

    int i = 0;
    for (auto it = text.cbegin(); it != text.cend(); ) {
        /* get utf8 char */
        tile.chr = utf8::next(it, text.cend());
        render_tile(x + i, y, tile);

        /* advance (and possibly wrap) */
        i++;
        if (wrap > 0 && i >= wrap) {
            i = 0;
            y++;
        }
    }
}

};
