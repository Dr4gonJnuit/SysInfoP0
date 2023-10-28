#include "my_functions.h"

uint8_t MY_HEAP[64000];

void init()
{
    MY_HEAP[0] = 0b11111010; // 1111 1010 0000 0000 = 64000, c'est la taille de la HEAP.
    MY_HEAP[1] = 0b00000000; // inutile mais bien de le rappeller qu'il fait partie du nombre qui calcule la taille de la HEAP.
    for (size_t i = 2; i < 64000; i++)
    {
        MY_HEAP[i] = 0;
    }
}

void my_free(void *pointer)
{
    /**********************
     * Libération du bloc *
     **********************/

    // Il y a deux blocs de métadonnée, seul le deuxième est important pour indiquer si le bloc est libre ou non.
    uint8_t *meta_block = (uint8_t *)(pointer - 1);
    // On met le bit de poids faible à zéro pour indiquer que le bloc est mtn libre.
    *meta_block &= ~0x1;

    /*************************************************************
     * Vérification s'il n'y a pas un autre bloc libre plus loin *
     *************************************************************/

    // On prend la taille du bloc et comme on l'a libéré, on sait que le bit de poids faible est égal à zéro.
    uint16_t block_free_size = (uint16_t)(*(meta_block - 1) << 8) | (uint16_t) * (meta_block);

    // Pointer pointe là où on veux écrire les données, pas le bloc de métadonnée.
    // En fesant -2 on obtient le début du bloc de métadonnée, là où se trouve les bits de poids fort.
    uint8_t *block_next = (uint8_t *)(pointer + block_free_size - 2);
    if ((*(block_next + 1) & 0x1) == 0)
    {
        /********************
         * Fusion des blocs *
         ********************/
        uint16_t block_next_size = (uint16_t)(*(block_next) << 8) | (uint16_t) * (block_next + 1);
        uint16_t combined_free_block = block_free_size + block_next_size;

        *(meta_block - 1) = (uint8_t)(combined_free_block >> 8);
        *meta_block = (uint8_t)combined_free_block;
    }
}

void *my_malloc(size_t size)
{
    // On pointe vers le premier élément de la HEAP
    uint8_t *pointer = MY_HEAP;

    // Taille de la HEAP
    size_t left_s = 64000;

    /******************************************
     * On cherche l'endroit où placer le bloc *
     ******************************************/

    // Taille du bloc qu'on est en train de lire sans le bit de poids faible
    uint16_t block_read_size = ((uint16_t)(*pointer << 8) | (uint16_t) * (pointer + 1)) & ~0x1;

    // Taille du bloc qu'on veut insérer.
    uint16_t block_insert_size;
    if (size % 2 != 0)
    {
        block_insert_size = size + 3; // On insert le bloc de métadonnée (2 bytes) + 1 pour avoir un nombre pair
    }
    else
    {
        block_insert_size = size + 2; // On insert le bloc de métadonnée (2 bytes)
    }

    // On cherche un endroit dans la heap où il y aurait de la place.
    int i = 2;
    while (left_s > 0 &&                           // On vérifie si on ne dépasse pas la HEAP
           ((*(pointer + 1) & 0x1) != 0 ||         // On regarde le deuxième byte (qui indique si le bloc est est libre ou non)
            block_read_size <= block_insert_size)) // On regarde s'il y a de la place avec les bytes de métadonnée
    {
        left_s -= block_read_size;                                                         // On enlève le nombre de byte disponible
        pointer = pointer + (block_read_size);                                             // On va à la prochaine métadonnée
        block_read_size = ((uint16_t)(*pointer << 8) | (uint16_t) * (pointer + 1)) & ~0x1; // On reprend la taille du nouveau bloc
        i++;
    }

    // Si on dépasse la taille de la heap, on doit retourner NULL.
    if (left_s <= 0)
    {
        return NULL;
    }

    /********************
     * On place le bloc *
     ********************/

    // Écrit le bloc de métadonnée avec la taille (plus le bloc) et attribue le bloc.
    uint16_t new_block = block_insert_size | 0x1;

    block_read_size &= ~0x1;

    uint16_t new_free_block = block_read_size - block_insert_size;

    // On insert les 8 bits de poids fort dans le premier byte et les 8 bits de poids faible dans le second byte
    *pointer = (uint8_t)(new_block >> 8);
    *(pointer + 1) = (int8_t)new_block;

    // Mettre la nouvelle taille du bloc libre
    if ((block_insert_size) < block_read_size)
    {
        *(pointer + block_insert_size) = (uint8_t)((new_free_block) >> 8);
        *(pointer + block_insert_size + 1) = (uint8_t)(new_free_block & ~0x1);
    }

    return (void *)pointer + 2; // On ne veut pas renvoyer un pointeur vers la métadonnée mais vers le premier byte ou on peut écrire.
}

// fct pour afficher les bytes en binaire
void bin(unsigned n, int t)
{
    unsigned i;
    for (i = 1 << t - 1; i > 0; i = i / 2)
        (n & i) ? printf("1") : printf("0");
    printf("\n");
}