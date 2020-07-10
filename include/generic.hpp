#include <iostream>
#include <string>
#include <memory>

/**
 * Endianess global constants are not defined in all OS.
 */

#if !defined(BIG_ENDIAN)
#define BIG_ENDIAN 4321
#endif // BIG_ENDIAN

#if !defined(LITTLE_ENDIAN)
#define LITTLE_ENDIAN 1234
#endif // LITTLE_ENDIAN

// namespace std
// {
//     template <typename T>
//     inline std::shared_ptr<T> make_shared(const size_t &size)
//     {
//         return std::shared_ptr<T>(new T[size], [](T *p) { delete[] p; });
//     }
// } // namespace std

namespace generic_funcs
{
    //smart pointer overload

    /**
 * Passes the given char pointers to the string constructor and returns it.
 */
    std::string bin_to_string(const unsigned char *end,
                              const unsigned char *length,
                              const int &endianness = BIG_ENDIAN);

    /**
 * interprets and casts the given array of bytes 
 * into an interger number (short, int, long...).
 * If the requested type cannot hold the given data, 0 is returned.
 */
    template <typename T, typename = std::enable_if_t<std::is_integral<T>::value>>
    T bin_to_number(const unsigned char *start,
                    const unsigned char *end,
                    const int &endianness = LITTLE_ENDIAN)
    {
        if (sizeof(T) < end - start)
        {
            return 0;
        }
        T ret = 0;
        while (end >= start)
        {
            if (endianness == BIG_ENDIAN)
            {
                ret = (ret << 8) + *start;
                start++;
            }
            else
            {
                ret = (ret << 8) + *end;
                end--;
            }
        }

        return ret;
    }

} // namespace generic_funcs