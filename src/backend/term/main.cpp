#include "TermDisplay.h"
#include "../../ui/UI.h"
#include <iostream>

using namespace term;
using namespace disp;

int main (int argc, char** argv)
{
    (void) argc;
    (void) argv;

    try {
        auto disp_ptr = new TermDisplay;
        auto& disp = (TermDisplay&) *disp_ptr;
        Display::set_instance(disp_ptr);
        
        ui::UI user_interface;
        for (;;) {
            /* display */
            disp.begin_draw();
            //disp.render_text(1, 1, "hello", disp::Color::white());
            user_interface.render(disp);
            disp.end_draw();

            /* handle events */
            if (auto action = disp.poll_user_action()) {
                if (*action == Action::quit)
                    break;
                else
                    user_interface.process_action(*action);
            }
        }
        return 0;
    }
    catch (std::runtime_error& err) {
        Display::set_instance(nullptr);
        std::cerr << "error: " << err.what() << std::endl;
        return 1;
    }    
}
