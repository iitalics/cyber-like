#pragma once
#include <string>

enum ControlCode {
    space=' ',
    tab='\t',
    left=0x100,
    right,
    up,
    down,
    quit,
};

struct Control {
    inline Control (int k=0)
        : code(k)
    {}
    
    int code;
    inline operator int () const { return code; }
    
    std::string str () const;
};
