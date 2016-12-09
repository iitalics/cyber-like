#pragma once
#include <cstdint>

namespace disp {

struct Color {
    uint8_t r, g, b;

    constexpr Color (uint8_t red, uint8_t green, uint8_t blue)
    : r(red), g(green), b(blue)
    {}
    constexpr Color ()
    : r(0), g(0), b(0)
    {}

    static inline constexpr Color rgb (int rgb24)
    {
        return Color((rgb24 >> 16) & 0xff,
                     (rgb24 >> 8)  & 0xff,
                     (rgb24)       & 0xff);
    }

    inline uint8_t operator[] (int i) const
    {
        switch (i) {
        case 0: return r;
        case 1: return g;
        case 2: return b;
        default: return 0;
        }
    }
    
    static inline constexpr Color black () { return rgb(0x000000); }
    static inline constexpr Color white () { return rgb(0xffffff); }
    static inline constexpr Color red () { return rgb(0xff0000); }
    static inline constexpr Color green () { return rgb(0x00ff00); }
    static inline constexpr Color blue () { return rgb(0x0000ff); }
    static inline constexpr Color cyan () { return rgb(0x00ffff); }
    static inline constexpr Color magenta () { return rgb(0xff00ff); }
    static inline constexpr Color yellow () { return rgb(0xffff00); }

    // i = 0,1,2,3,4,5
    static inline constexpr Color grey (int i = 3) { return rgb(0x333333 * i); }
};

}
