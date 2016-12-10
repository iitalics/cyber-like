#include "Display.h"
#include <utf8.h>

namespace disp {

std::unique_ptr<Display> Display::instance_ = nullptr;

Display::~Display () {}

void Display::set_instance (Display* d)
{
    instance_.reset(d);
}

void Display::render_text (int x, int y,
                           boost::string_ref text,
                           boost::string_ref font, int wrap)
{
    auto tile_name = font.to_string();
    
    int i = 0;
    for (auto it = text.cbegin(); it != text.cend(); ) {
        /* get utf8 char */
        uint32_t chr;
        try {
            chr = utf8::next(it, text.cend());
        }
        catch (utf8::exception& utf_err) {
            return;
        }

        if (chr != ' ') {
            // e.g:
            // chr = 'a', font = "xyz"
            // =>  tile_name = "xyz-a"
            tile_name.resize(font.size());
            tile_name.push_back('-');
            utf8::append(chr, std::back_inserter(tile_name));
            render_tile(x + i, y, tile_set->tile_by_name(tile_name));
        }

        /* advance (and possibly wrap) */
        i++;
        if (wrap > 0 && i >= wrap) {
            i = 0;
            y++;
        }
    }
}

};
