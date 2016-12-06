#include "TermDisplay.h"

using namespace term;
using namespace disp;

int main (int argc, char** argv)
{
  (void) argc;
  (void) argv;

  auto disp = new TermDisplay;
  Display::set_instance(disp);

  while (!disp->quit()) {
    disp->begin_draw();
    disp->render_tile(5, 5,
                      Tile('@', Color::white()));

    struct tb_cell c;
    c.ch = '@';
    c.fg = 0x2;
    c.bg = 0x0;
    tb_put_cell(1, 1, &c);
    
    disp->end_draw();
  }
  
  return 0;
}
