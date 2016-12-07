#include "TermDisplay.h"

namespace term {


TermDisplay::TermDisplay ()
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
    int r = (col.r * 5 + 0x7f) / 0xff;
    int g = (col.g * 5 + 0x7f) / 0xff;
    int b = (col.b * 5 + 0x7f) / 0xff;

    /*    if (r == g && g == b) {
        int grey = (col.r + col.g + col.b) * 24 / 0xff / 3;
        return 0xe8 + grey;
    }
    else */
        return 0x10 + (r * 36 + g * 6 + b);
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
}

boost::optional<Control> TermDisplay::poll_ctrl_event ()
{
    boost::optional<Control> retval;

    struct tb_event evt;
    switch (tb_poll_event(&evt)) {
    case TB_EVENT_KEY:
        switch (evt.key) {
        case TB_KEY_CTRL_Q:
            retval.reset(ControlCode::quit); break;
        case TB_KEY_ARROW_LEFT:
            retval.reset(ControlCode::left); break;
        case TB_KEY_ARROW_RIGHT:
            retval.reset(ControlCode::right); break;
        case TB_KEY_ARROW_UP:
            retval.reset(ControlCode::up); break;
        case TB_KEY_ARROW_DOWN:
            retval.reset(ControlCode::down); break;
        }
        break;

    case -1:
        /* error */
        throw Error("TermDisplay event error");

    default:
        break;
    }

    return retval;
}

void TermDisplay::render_tile (int x, int y, const disp::Tile& tile)
{
    if (x < 0 || x >= tb_width() || y < 0 || y >= tb_height())
        return;

    auto cell_buf = tb_cell_buffer();
    auto& out_cell = cell_buf[x + y * tb_width()];

    out_cell.ch = tile.chr;
    if (!tile.transparent) {
        out_cell.bg = conv_color_(tile.bg);
    }
    out_cell.fg = conv_color_(tile.fg);
}

}
