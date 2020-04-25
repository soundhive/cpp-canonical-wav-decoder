#include <generic.hpp>

int char_array_to_number(const char *start, const char *end, const bool &big_endian /* = false */)
{
    int ret = 0;

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
    return ret;
}






std::string char_array_to_string(const char *start, const char *end, const bool &big_endian /* = true */)
{
    if (start == nullptr || end == nullptr)
        return "";
    end++;
    return std::string(start, end);
}