#include <stdlib.h>
#include <stdio.h>

int main (int argc, char *argv[])
{
    char chaine[6];

    chaine[0] = 'S';
    chaine[1] = 'a';
    chaine[2] = 'l';
    chaine[3] = 'u';
    chaine[4] = 't';
    chaine[5] = '\0';

    printf("%s\n", chaine);

    return 0;
}