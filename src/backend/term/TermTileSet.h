#include "TermDisplay.h"
#include <vector>
#include <unordered_map>
#include <fstream>

namespace term {

struct TermTileSet : public disp::TileSet {
    TermTileSet (std::vector<TermCell>& tiles);
    virtual ~TermTileSet ();

    virtual id tile_by_name (boost::string_ref name);
    virtual id tile_for_char (uint32_t chr, disp::Color col);

    virtual void load_from_directory (boost::string_ref path);
    void parse_tileset_line (boost::string_ref line);
    void generate_tile (std::string name,
                        uint32_t repr,
                        disp::Color fg,
                        boost::optional<disp::Color> bg);
    void generate_font (std::string font_prefix,
                        disp::Color fg,
                        boost::optional<disp::Color> bg);

    std::vector<TermCell>& tiles;
    std::unordered_map<std::string, id> name_mapping;

    std::ofstream log_file;
};



}
