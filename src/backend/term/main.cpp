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
        disp->render_tile(4, 5, Tile('>', Color::red()));
        disp->render_tile(5, 5, Tile('@', Color::white()));
        disp->render_tile(6, 5, Tile('<', Color::cyan()));
        disp->end_draw();
    }
  
    return 0;
}
