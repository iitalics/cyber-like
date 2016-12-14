#pragma once
#include <string>

struct Action {
    enum {
        quit,
        left, right, up, down,
    };

    inline Action (int kind_)
        : kind(kind_)
    {}

    inline bool operator== (int x) const { return kind == x; }
    inline bool operator!= (int x) const { return kind != x; }
    inline operator int () const { return kind; }
    
    int kind;
    std::string to_string () const;
};
