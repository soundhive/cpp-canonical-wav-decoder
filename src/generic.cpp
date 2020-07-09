#include <generic.hpp>
#include <memory>
namespace gf = generic_funcs;

namespace std
{
    template <typename T>
    inline std::shared_ptr<T> make_shared(const size_t &size)
    {
        return std::shared_ptr<T>(new T[size], [](T *p) { delete[] p; });
    }
} // namespace std

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
            end--;
        }
        return res;
    }
}
