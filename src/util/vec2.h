#pragma once

/**
   2-dimensional vector class, parametric over the type of coordinates
 */
template <typename T>
struct vec2 {
    /**
       X coordinate of the vector.
    */
    T x;

    /**
       Y coordinate of the vector.
    */
    T y;

    /**
       Default constructor.

       Initializes a zero-vector (0, 0)
    */
    inline constexpr vec2 () : x(0), y(0) {}

    /**
       Constructor to create a vector from coordinates.
       @param x_ initial X coordinate.
       @param y_ initial Y coordinate.
     */
    inline constexpr vec2 (T x_, T y_) : x(x_), y(y_)
    {}

    /**
       Create a zero vector (0, 0).
    */
    inline static constexpr vec2 zero () { return vec2(0, 0); }
    /**
       Create a one vector (1, 1).
    */
    inline static constexpr vec2 one () { return vec2(1, 1); }
    /**
       Create a left vector (-1, 0).
    */
    inline static constexpr vec2 left () { return vec2(-1, 0); }
    /**
       Create a right vector (+1, 0).
    */
    inline static constexpr vec2 right () { return vec2(1, 0); }
    /**
       Create an upward vector (0, -1).
    */
    inline static constexpr vec2 up () { return vec2(0, -1); }
    /**
       Create a downward vector (0, +1).
    */
    inline static constexpr vec2 down () { return vec2(0, 1); }

    /**
       Add a vector to this vector.
       @param b the vector to add.
    */
    inline vec2& operator+= (vec2 b)
    {
        x += b.x;
        y += b.y;
        return *this;
    }
    /**
       Subtract a vector from this vector.
       @param b the vector to subtract.
    */
    inline vec2& operator-= (vec2 b)
    {
        x -= b.x;
        y -= b.y;
        return *this;
    }
    /**
       Multiply this vector by a scalar.
       @param a the scalar multiple.
    */
    inline vec2& operator*= (T a)
    {
        x *= a;
        y *= a;
        return *this;
    }

    /**
       Access a component of this vector by index.
       @param i coordinate index:
       @code 
       v[0] == v.x
       v[1] == v.y
       @endcode
    */
    inline constexpr T operator[] (unsigned int i) const {
        switch (i) {
        case 0: return x;
        case 1: return y;
        default: return 0;
        }
    }

    /**
       Cast this vector to another kind of vector.
    */
    template <typename U>
    inline constexpr operator vec2<U> () const {
        return vec2<U>(U(x), U(y));
    }
};

/**
   Alias for integer vector: vec2<int>
*/
using ivec = vec2<int>;
/**
   Alias for wide integer vector: vec2<long long int>
*/
using lvec = vec2<long long int>;
/*
  Alias for floating-point vector: vec2<float>
*/
using fvec = vec2<float>;

template <typename T>
inline constexpr vec2<T> operator+ (vec2<T> a, vec2<T> b) { return vec2<T>(a.x + b.x, a.y + b.y); }

template <typename T>
inline constexpr vec2<T> operator- (vec2<T> a, vec2<T> b) { return vec2<T>(a.x - b.x, a.y - b.y); }

template <typename T>
inline constexpr vec2<T> operator* (vec2<T> v, T a) { return vec2<T>(v.x * a, v.y * a); }

template <typename T>
inline constexpr bool operator== (vec2<T> a, vec2<T> b) { return a.x == b.x && a.y == b.y; }

template <typename T>
inline constexpr bool operator!= (vec2<T> a, vec2<T> b) { return a.x != b.x || a.y != b.y; }
