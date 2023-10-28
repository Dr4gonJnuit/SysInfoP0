#include "my_functions.h"

int main(int argc, char const **argv)
{
	init();

	extern uint8_t MY_HEAP[];

	void *b1 = my_malloc(1);
	void *b2 = my_malloc(17);
	void *b3 = my_malloc(13);
	void *b4 = my_malloc(8);
	void *b5 = my_malloc(63900);
	void *b6 = my_malloc(60);

	printf("Start Free Third Malloc :\n");
	my_free(b3);
	printf("End Free of the Third Malloc\n\nResult :\n");

	void *b3_2 = my_malloc(5);
	my_free(b3_2);

	for (size_t i = 0; i < (1+3+17+3+13+3+8+2+5); i++)
	{
		if (i == (1+3) || i == (1+3+17+3) || i == (1+3+17+3+13+3) || i==(1+3+17+3+13+3+8+2))
		{
			printf("\n");
		}
		
		bin(MY_HEAP[i], 8);
	}

	return 0;
}
