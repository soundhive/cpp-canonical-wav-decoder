#include <generic.hpp>

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
    else
    {
        std::string res = "";
        while (start <= end)
        {
            res += *end;
            end --;
        }
        return res;
    }
}
