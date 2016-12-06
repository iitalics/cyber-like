#include "TermDisplay.h"

using namespace term;
using namespace disp;


static Color mat[] =
    {
        Color::white(), Color::cyan(),
        Color::yellow(), Color::green(),
    };

Color lerp4 (float x, float y)
{
    uint8_t v[3];

    for (int i = 0; i < 3; i++) {
        float v1 = mat[0][i] + (mat[1][i] - mat[0][i]) * x;
        float v2 = mat[2][i] + (mat[3][i] - mat[2][i]) * x;
        v[i] = v1 + (v2 - v1) * y;
    }

    return Color(v[0], v[1], v[2]);
}

int main (int argc, char** argv)
{
    (void) argc;
    (void) argv;

    auto disp = new TermDisplay;
    Display::set_instance(disp);

    while (!disp->quit()) {
        disp->begin_draw();

        for (int y = 0; y < disp->height(); y++) {
            for (int x = 0; x < disp->width(); x++) {
                auto col = lerp4(x / float(disp->width()),
                                 y / float(disp->height()));
                disp->render_tile(x, y,
                                  Tile(' ', Color::black(), col));
            }
        }
        
        disp->end_draw();
    }
  
    return 0;
}
