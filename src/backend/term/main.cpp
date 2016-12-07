#include "TermDisplay.h"
#include "../../ui/UI.h"

using namespace term;
using namespace disp;

int main (int argc, char** argv)
{
    (void) argc;
    (void) argv;

    Display::set_instance(new TermDisplay);
    auto& disp = (TermDisplay&) *Display::instance();

    game::GameState game_state;
    ui::UI user_interface(game_state);
    
    while (! disp.quit()) {
        disp.begin_draw();
        user_interface.render(disp);
        disp.end_draw();
    }
  
    return 0;
}
