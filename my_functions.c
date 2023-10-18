#include "my_functions.h"

uint8_t MY_HEAP[64000];

void init()
{
    // Basics mais on peut s'en passer p'tete
    for (size_t i = 0; i < 64000; i++)
    {
        MY_HEAP[i] = 0;
    }
}

void my_free(void *pointer)
{
    // parait trop simple mais bon ça doit être fonctionnel ?
    uint8_t *starting_blocks = (uint8_t *)pointer - 1;
    // Alors la en gros c'est une porte AND en C
    *starting_blocks &= 0x7F;
}

// Fonction my_malloc
void *my_malloc(size_t size)
{
    uint8_t *pointer = MY_HEAP;
    size_t left_s = 64000;

    while (left_s >= size)
    {

        // Si le bloc est libre
        if (*pointer & 0x80 == 0)
        /* JB : on ne vérifie que le bit de poids fort
         * car avant si on avait "0101 1110" c'était pas libre
         * alors que ça devrait l'être. (1000 0000 = occupé, 0000 0000 = libre)
         */
        {
            size_t block_size = *pointer & 0x7F; // JB : Il y a ds le byte, à l'exception du bit de poids fort, la taille de l'espace disponible ou utilisé.

            // JB : Si la taille est égale à 0 ça veut dire qu'on a rien alloué encore
            if (block_size == 0)
            {
                *pointer = (uint8_t)size | 0x80;
            }

            // Pas sur de ça mais le cours dis oui ? si tu sais donner ton avis
            // JB : separation du block si la taille est plus grande je dirais.
            if (block_size >= size)
            {
                *pointer = (uint8_t)size | 0x80; // JB : on met ds le bloc de métadonée la taille qu'on alloue + le "1" ds le bit de poids fort
                block_size -= size;              // JB : on vérifie l'espace restant

                if (block_size == 0)
                {
                    break; // return (void *) (&pointer);
                }
            }
            // JB : block_size = size si on est à la fin ou le reste si on a fragmenté la zone en deux
            pointer += block_size;
            *pointer = (uint8_t)block_size & 0x7F; // JB : on garde la taille si on fragmente, sinon ça reste à zéro
        }
        else
        {
            // Passer au bloc suivant
            size_t block_size = (*pointer) & 0x7F;
            pointer += block_size;
            left_s -= block_size;
        }
    }
    return NULL;
}