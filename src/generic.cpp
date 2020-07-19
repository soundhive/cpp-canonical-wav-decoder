#include <generic.hpp>
#include <memory>
namespace gf = generic_funcs;



std::string gf::bin_to_string(const unsigned char *start,
                              const unsigned char *end,
                              const int &endianness)
{
    auto str = std::string(start, end + 1);

    if (endianness == BIG_ENDIAN)
    {
        return str;
    }
    else if (endianness == LITTLE_ENDIAN)
    {
        std::reverse(str.begin(), str.end());
        return str;
    }

    throw new std::invalid_argument("Wrong endianess value.");
}
