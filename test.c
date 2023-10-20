#include "my_functions.h"

int main(int argc, char const *argv[])
{
    uint8_t dec = 0b00001110;

    dec = (dec >> 1);

    bin(dec);

    return 0;
}
