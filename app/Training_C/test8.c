#include <stdlib.h>
#include <stdio.h>

int sommeTableau(int tableau[], int tailleTableau);
double moyenneTableau(int tableau[], int tailleTableau);

int main(int argc, char *argv[])
{
    int tableau[5] = {10, 15, 3, 26, 78};
    printf("%d\n", sommeTableau(tableau, 5));
    printf("%f\n", moyenneTableau(tableau, 5));
    return 0;
}
int sommeTableau(int tableau[], int tailleTableau)
{
    int i;
    int somme = 0;
    for (i = 0; i < tailleTableau; i++)
    {
        somme += tableau[i];
    }
    return somme;
}
double moyenneTableau(int tableau[], int tailleTableau)
{
    int somme = 0;
    for (int i = 0; i < tailleTableau; i++)
    {
        somme += tableau[i];
    }
    return (double)somme/(double)tailleTableau;
}