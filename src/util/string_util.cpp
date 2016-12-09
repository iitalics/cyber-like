#include "string_util.h"
#include <algorithm>

namespace misc {

boost::string_ref trim_left (boost::string_ref s, boost::string_ref ws)
{
    size_t n;
    for (n = 0; n < s.size(); n++) {
        if (ws.end() ==
            std::find_if(ws.begin(), ws.end(),
                         [&] (char wsc) { return s[n] == wsc; }))
            break;
    }
    return s.substr(n);
}

boost::string_ref trim_right (boost::string_ref s, boost::string_ref ws)
{
    size_t n;
    for (n = s.size(); n != 0; n--) {
        if (ws.end() ==
            std::find_if(ws.begin(), ws.end(),
                         [&] (char wsc) { return s[n - 1] == wsc; }))
            break;
    }
    return s.substr(0, n);
}


boost::string_ref trim_both (boost::string_ref s, boost::string_ref ws)
{
    return trim_left(trim_right(s, ws));
}

}
