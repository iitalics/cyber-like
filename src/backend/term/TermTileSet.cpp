#include "TermTileSet.h"
#include "TermDisplay.h"
#include "../../util/string_util.h"
#include <boost/format.hpp>
#include <boost/regex.hpp>
#include <fstream>
#include <stdexcept>
#include <utf8.h>

namespace term {

using namespace disp;

TermTileSet::TermTileSet (std::vector<TermCell>& origin_tiles)
    : tiles(origin_tiles)
    , log_file("log.term-tile-set.txt")
{}

TermTileSet::~TermTileSet ()
{}

TileSet::id TermTileSet::tile_by_name (boost::string_ref name)
{
    auto it = name_mapping.find(name.to_string());
    if (it == name_mapping.end()) {
        return missing_id;
    }
    else {
        return it->second;
    }
}

TileSet::id TermTileSet::tile_for_char (uint32_t chr, disp::Color col)
{
    auto name = (boost::format("(char-%d-%d)")
                 % chr % TermDisplay::conv_color(col)).str();
    auto id = tile_by_name(name);
    if (id == missing_id) {
        id = name_mapping[name] = tiles.size();
        tiles.push_back(TermCell { chr, col, Color(), true });
    }
    return id;
}

void TermTileSet::load_from_directory (boost::string_ref dir_path)
{
    auto path = dir_path.to_string();
    path += "/term.tiles.txt";

    std::ifstream input_file(path);
    if (!input_file) {
        auto fmt = boost::format("could not load tileset file: %s") % path;
        throw std::runtime_error(fmt.str());
    }

    /* TODO: try / catch & log */
    std::string line;
    while (!input_file.eof()) {
        line.clear();
        std::getline(input_file, line);

        auto trimmed = misc::trim_both(line);
        if (!trimmed.empty() && trimmed[0] != '#') {
            parse_tileset_line(trimmed);
        }
    }
}


using regex_result = boost::match_results<boost::string_ref::iterator>;
/*
  line := name repr fg bg
  repr := '[' chr ']' | '(' hex hex hex hex ')'
  fg := hex hex hex
  bg := hex hex hex | '-'
*/
static boost::regex line_regex("^(\\S+)\\s+"
                                "(\\[.\\]|\\([0-9a-f]{4}\\))\\s+"
                                "([0-9a-f]{3})\\s+"
                                "([0-9a-f]{3}|\\-)\\s*$");

static inline uint8_t hex2int (char c)
{
    if ('0' <= c && c <= '9')
        return c - '0';
    else
        return c - 'a' + 10;
}

static inline Color hex_color (boost::string_ref s)
{
    int r = hex2int(s[0]);
    int g = hex2int(s[1]);
    int b = hex2int(s[2]);
    return Color(r * 0x11, g * 0x11, b * 0x11);
}

void TermTileSet::parse_tileset_line (boost::string_ref line)
{
    regex_result rr;

    if (boost::regex_match(line.begin(), line.end(), rr, line_regex)) {
        auto name = rr[1].str();
        auto repr = rr[2].str();

        uint32_t chr;
        if (repr[0] == '(') {
            uint8_t n3 = hex2int(repr[1]);
            uint8_t n2 = hex2int(repr[2]);
            uint8_t n1 = hex2int(repr[3]);
            uint8_t n0 = hex2int(repr[4]);
            chr = n0 | (n1 * 16) | (n2 * 16 * 16) | (n3 * 16 * 16 * 16);
        }
        else {
            chr = repr[1];
        }

        auto fg = hex_color(rr[3].str());
        auto bg = boost::optional<Color>();
        if (rr[4] != "-") {
            bg.reset(hex_color(rr[4].str()));
        }

        if (boost::string_ref(name).ends_with("-?") && chr == '?') {
            log_file << "generating font: " << name << std::endl;
            name.pop_back(); // remove ?
            generate_font(std::move(name), fg, bg);
        }
        else {
            log_file << "generating tile: " << name << std::endl;
            generate_tile(std::move(name), chr, fg, bg);
        }
    }
}

void TermTileSet::generate_tile (std::string name,
                                 uint32_t repr,
                                 disp::Color fg,
                                 boost::optional<disp::Color> bg)
{
    name_mapping[std::move(name)] = tiles.size();
    if (bg)
        tiles.push_back(TermCell { repr, fg, *bg, false });
    else
        tiles.push_back(TermCell { repr, fg, Color(), true });
}

void TermTileSet::generate_font (std::string font_name,
                                 disp::Color fg,
                                 boost::optional<disp::Color> bg)
{
    const size_t base_font_name_size = font_name.size();

    for (int c = 1; c < 128; c++) {
        font_name.resize(base_font_name_size);
        utf8::append(c, std::back_inserter(font_name));
        generate_tile(font_name, c, fg, bg);
    }
}

}
