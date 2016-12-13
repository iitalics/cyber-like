#include <string>
#include <boost/utility/string_ref.hpp>

namespace misc {

/**
   Trim leading whitespace, in a string.
   Returns a substring of the given string, with leading whitespace removed.
   @param s string to trim.
   @param ws set of whitespace characters to trim (optional).
 */
extern boost::string_ref trim_left (boost::string_ref s,
                                    boost::string_ref ws=" \t\r\n\b\f");

/**
   Trim trailing whitespace, in a string.
   Returns a substring of the given string, with trailing whitespace removed.
   @param s string to trim.
   @param ws set of whitespace characters to trim (optional).
 */
extern boost::string_ref trim_right (boost::string_ref s,
                                    boost::string_ref ws=" \t\r\n\b\f");

/**
   Trim leading and trailing whitespace, in a string.
   Returns a substring of the given string, with leading & trailing whitespace removed.
   @param s string to trim.
   @param ws set of whitespace characters to trim (optional).
 */
extern boost::string_ref trim_both (boost::string_ref s,
                                    boost::string_ref ws=" \t\r\n\b\f");

}
