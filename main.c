#include "my_functions.h"

int main(int argc, char const **argv)
{
    printf("Start\n");

    printf("Init\n");

    init();

    printf("End Init\n");

    extern uint8_t MY_HEAP[];

    for (size_t i = 0; i < 20; i++)
    {
        bin(MY_HEAP[i]);
    }

    printf("First Malloc\n");
    
    void *b1 = my_malloc(1);

    printf("End First Malloc\n");

    for (size_t i = 0; i < 20; i++)
    {
        bin(MY_HEAP[i]);
    }

    
    void *b2 = my_malloc(17);
    void *b3 = my_malloc(13);

    for (size_t i = 0; i < 20; i++)
    {
        bin(MY_HEAP[i]);
    }
    
    /*
    my_free(b3);
    */
    printf("End\n");

    return 0;
}
