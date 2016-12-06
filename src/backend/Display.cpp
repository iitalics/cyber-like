#include "Display.h"

namespace disp {

std::unique_ptr<Display> Display::instance_ = nullptr;

Display::~Display () {}

void Display::set_instance (Display* d)
{
  instance_.reset(d);
}

};
