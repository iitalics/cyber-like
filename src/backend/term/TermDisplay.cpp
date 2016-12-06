#include "TermDisplay.h"

namespace term {


TermDisplay::TermDisplay ()
    : quit_(false)
{
    tb_init();
    tb_select_input_mode(TB_INPUT_MOUSE);
    tb_select_output_mode(TB_OUTPUT_256);
}

TermDisplay::~TermDisplay ()
{
    tb_shutdown();
}

uint16_t TermDisplay::conv_color_ (disp::Color col)
{
    int r = col.r * 5 / 0xff;
    int g = col.g * 5 / 0xff;
    int b = col.b * 5 / 0xff;

    if (r == g && g == b) {
        int grey = (col.r + col.g + col.b) * 24 / 0xff / 3;
        return 0xe8 + grey;
    }
    else {
        return 0x10 + (r * 36 + g * 6 + b);
    }
}

void TermDisplay::begin_draw ()
{
    width_ = tb_width();
    height_ = tb_height();
    tb_set_clear_attributes(0x10, 0x10); // black
    tb_clear();
}

void TermDisplay::end_draw ()
{
    tb_present();
    struct tb_event evt;
    switch (tb_poll_event(&evt)) {
    case TB_EVENT_KEY:
        /* ^Q */
        if (evt.key == TB_KEY_CTRL_Q)
            quit_ = true;
        break;

    case -1:
        /* error */
        quit_ = true;
        throw Error("TermDisplay event error");

    default:
        break;
    }
}

void TermDisplay::render_tile (int x, int y, const disp::Tile& tile)
{
    auto cell_buf = tb_cell_buffer();
    auto& out_cell = cell_buf[x + y * width_];

    out_cell.ch = tile.chr;
    if (!tile.transparent) {
        out_cell.bg = conv_color_(tile.bg);
    }
    out_cell.fg = conv_color_(tile.fg);
}

}
