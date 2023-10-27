#include "my_functions.h"

int main(int argc, char const **argv)
{
	printf("Start Init :\n");

	init();

	extern uint8_t MY_HEAP[];

	printf("End Init\n\nResult Init :\n");

	for (size_t i = 0; i < 10; i++)
	{
		bin(MY_HEAP[i], 8);
	}

	printf("\nStart First Malloc :\n");

	void *b1 = my_malloc(1);

	printf("End First Malloc\n\nResult First Malloc :\n");

	for (size_t i = 0; i < 10; i++)
	{
		bin(MY_HEAP[i], 8);
	}

	printf("\nStart Second Malloc :\n");

	void *b2 = my_malloc(17);

	printf("End Second Malloc\n\nResult Second Malloc :\n");

	for (size_t i = 0; i < 25; i++)
	{
		bin(MY_HEAP[i], 8);
	}

	printf("\nStart Third Malloc :\n");

	void *b3 = my_malloc(13);

	printf("End Third Malloc\n\nResult Third Malloc :\n");

	for (size_t i = 0; i < 50; i++)
	{
		bin(MY_HEAP[i], 8);
	}

	printf("\nStart Fourth Malloc :\n");

	void *b4 = my_malloc(8);

	printf("End Fourth Malloc\n\nResult Fourth Malloc :\n");

	for (size_t i = 0; i < 60; i++)
	{
		bin(MY_HEAP[i], 8);
	}

	printf("\nStart Fourth Malloc :\n");

	void *b5 = my_malloc(63900);

	printf("End Fifth Malloc\n");//\nResult Fifth Malloc :\n");
	/*
	for (size_t i = 0; i < 60; i++)
	{
		bin(MY_HEAP[i], 8);
	}
	*/

	printf("\nStart Sixth Malloc :\n");

	void *b6 = my_malloc(60);

	printf("End Sixth Malloc\n");//\nResult Sixth Malloc :\n");
	/*
	for (size_t i = 0; i < 60; i++)
	{
		bin(MY_HEAP[i], 8);
	}
	*/

	/*
	my_free(b3);
	*/

	return 0;
}
