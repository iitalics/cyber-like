#include "TermDisplay.h"
#include "../../ui/UI.h"

using namespace term;
using namespace disp;

int main (int argc, char** argv)
{
    (void) argc;
    (void) argv;

    auto disp_ptr = new TermDisplay;
    auto& disp = (TermDisplay&) *disp_ptr;
    Display::set_instance(disp_ptr);

    {
        ui::UI user_interface;
        for (bool quit = false; ! quit; ) {
            /* display */
            disp.begin_draw();
            user_interface.render(disp);
            disp.end_draw();

            /* handle events */
            if (auto maybe_ctrl = disp.poll_ctrl_event()) {
                if (*maybe_ctrl == ControlCode::quit)
                    quit = true;
                else
                    user_interface.process_control(*maybe_ctrl);
            }
        }

    }
    
    return 0;
}
