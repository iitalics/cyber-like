#pragma once
#include <vector>
#include <stdexcept>
#include <backend/Display.h>

#include <termbox.h>

namespace term {

using Error = std::runtime_error;

struct TermDisplay : public disp::Display {
  TermDisplay ();
  virtual ~TermDisplay ();

  virtual void render_tile (int x, int y, const disp::Tile& t);
  virtual void begin_draw ();
  virtual void end_draw ();

  bool quit () const { return quit_; }
private:
  static uint16_t conv_color_ (disp::Color col);
  bool quit_;
};

}
