#include "my_functions.h"

int main(int argc, char const **argv)
{
    init();

    void *b1 = my_malloc(1);
    void *b2 = my_malloc(17);
    void *b3 = my_malloc(13);
  
    //my_free(b3);
    printf("C'est ok !");

    return 0;
}
