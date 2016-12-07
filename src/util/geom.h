#pragma once

template <typename T>
struct vec2 {
    T x, y;
    inline constexpr vec2 (T x_, T y_) : x(x_), y(y_)
    {}
    inline constexpr vec2 () : x(0), y(0) {}

    inline static constexpr vec2 zero () { return vec2(0, 0); }
    inline static constexpr vec2 one () { return vec2(1, 1); }
    inline static constexpr vec2 left () { return vec2(-1, 0); }
    inline static constexpr vec2 right () { return vec2(1, 0); }
    inline static constexpr vec2 up () { return vec2(0, -1); }
    inline static constexpr vec2 down () { return vec2(0, 1); }

    inline constexpr vec2 operator+ (vec2 b) const { return vec2(x + b.x, y + b.y); }
    inline constexpr vec2 operator- (vec2 b) const { return vec2(x - b.x, y - b.y); }
    inline constexpr vec2 operator* (T a) const { return vec2(x * a, y * a); }
    inline constexpr vec2 operator- () const { return vec2(-x, -y); }
    inline constexpr vec2 operator== (vec2 b) const { return x == b.x && y == b.y; }
    inline constexpr vec2 operator!= (vec2 b) const { return x == b.x && y == b.y; }

    inline vec2& operator+= (vec2 b)
    {
        x += b.x;
        y += b.y;
        return *this;
    }
    inline vec2& operator-= (vec2 b)
    {
        x -= b.x;
        y -= b.y;
        return *this;
    }
    inline vec2& operator*= (T a)
    {
        x *= a;
        y *= a;
        return *this;
    }

    inline constexpr T operator[] (unsigned int i) const {
        switch (i) {
        case 0: return x;
        case 1: return y;
        default: return 0;
        }
    }

    template <typename U>
    inline constexpr operator vec2<U> () const {
        return vec2<U>(U(x), U(y));
    }
};

using ivec = vec2<int>;
using lvec = vec2<long long int>;
using fvec = vec2<float>;
