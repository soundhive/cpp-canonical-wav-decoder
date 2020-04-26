#include <iostream>
#include <string>

#include <string.h>

int char_array_to_number(const unsigned char *start,
                     const unsigned char *end,
                     const bool &big_endian = false);




std::string char_array_to_string(const unsigned char *end,
                                 const unsigned char *length);
