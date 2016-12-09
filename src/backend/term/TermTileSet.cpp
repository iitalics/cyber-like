#include "TermTileSet.h"
#include "TermDisplay.h"
#include "../../util/string_util.h"
#include <boost/format.hpp>
#include <boost/regex.hpp>
#include <fstream>
#include <stdexcept>

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

static boost::regex line_regexp("^(\\S+)\\s+"
                                "\\[(.+)\\]\\s+"
                                "(\\S\\S\\S)\\s+"
                                "(\\S\\S\\S|\\-)");

void TermTileSet::parse_tileset_line (boost::string_ref line)
{
    boost::match_results<boost::string_ref::iterator> mr;

    if (boost::regex_match(line.begin(), line.end(), mr, line_regexp)) {
        auto& name = mr[1];
        auto& repr = mr[2];
        // auto& fg = mr[3];
        // auto& bg = mr[4];
        log_file << "new tile: " << name << ", repr = [" << repr << "]" << std::endl;

        name_mapping[name] = tiles.size();
        tiles.push_back(TermCell { '?', Color::blue(), Color::magenta(), false });
    }
}


}
