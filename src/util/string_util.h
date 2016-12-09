#include <string>
#include <boost/utility/string_ref.hpp>

namespace misc {

extern boost::string_ref trim_left (boost::string_ref s,
                                    boost::string_ref ws=" \t\r\n\b\f");
extern boost::string_ref trim_right (boost::string_ref s,
                                    boost::string_ref ws=" \t\r\n\b\f");
extern boost::string_ref trim_both (boost::string_ref s,
                                    boost::string_ref ws=" \t\r\n\b\f");

}
