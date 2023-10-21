#include "my_functions.h"

int main(int argc, char const **argv)
{
    init();

    extern uint8_t MY_HEAP[];

    void *b1 = my_malloc(1);
    void *b2 = my_malloc(17);
    void *b3 = my_malloc(13);

    for (size_t i = 0; i < 50; i++)
    {
        bin(MY_HEAP[i]);
    }
    
    /*
    my_free(b3);
    */

    return 0;
}
