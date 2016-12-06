#pragma once
#include <cstdint>
#include <memory>

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

  static inline constexpr Color black ()
  { return rgb(0x000000); }
  static inline constexpr Color grey ()
  { return rgb(0x7f7f7f); }
  static inline constexpr Color white ()
  { return rgb(0xffffff); }
  static inline constexpr Color red ()
  { return rgb(0xff0000); }
  static inline constexpr Color green ()
  { return rgb(0x00ff00); }
  static inline constexpr Color blue ()
  { return rgb(0x0000ff); }
};

struct Tile {
  bool transparent;
  Color fg, bg;
  uint32_t chr;

  Tile (uint32_t c, Color f)
    : transparent(true)
    , fg(f), chr(c)
  {}

  Tile (uint32_t c, Color f, Color b, bool transp = false)
    : transparent(transp)
    , fg(f), bg(b), chr(c)
  {}
};



class Display {
public:
  virtual ~Display () = 0;

  /* interface */
  virtual void render_tile (int x, int y, const Tile& t) = 0;
  virtual void begin_draw () = 0;
  virtual void end_draw () = 0;

  /* dimensions */
  inline int width () const { return width_; }
  inline int height () const { return height_; }

  /* singleton */
  static Display* instance () { return instance_.get(); }
  static void set_instance (Display* to);
  
protected:
  int width_, height_;
  
private:
  static std::unique_ptr<Display> instance_;
};


}
