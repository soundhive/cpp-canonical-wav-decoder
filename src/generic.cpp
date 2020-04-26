#include <generic.hpp>

int char_array_to_number(const unsigned char *start, const unsigned char *end, const bool &big_endian /* = false */)
{
    uint32_t ret = 0;

    while (end >= start)
    {
        if (big_endian){
            ret = (ret << 8) + *start;
            start++;
        } else {
            ret = (ret << 8) + *end;
            end--;
        }
        
    }
    return *reinterpret_cast<int*>(&ret);
}






std::string char_array_to_string(const unsigned char *start, const unsigned char *end)
{
    if (start == nullptr || end == nullptr)
        return "";
    end++;
    return std::string(start, end);
}