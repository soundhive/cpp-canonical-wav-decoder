#include <generic.hpp>
#include <memory>
namespace gf = generic_funcs;

std::string gf::bin_to_string(const unsigned char *start,
                              const unsigned char *end,
                              const int &endianness)
{
    if (endianness == BIG_ENDIAN)
    {
        end++;
        return std::string(start, end);
    }
    else if (endianness == LITTLE_ENDIAN)
    {
        std::string res = "";
        while (start <= end)
        {
            res += *end;
            end--;
        }
        return res;
    }
    else
    {
        throw new std::invalid_argument("Wrong endianess value.");
    }
}
