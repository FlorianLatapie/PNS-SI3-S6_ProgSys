#include<stdio.h>
#include<stdlib.h>


int rechercheBinaire(int tab[],int x,int i, int j){
    int gau,droite,milieu;
    gau=i;droite=j;
    while (gau<=droite) {
        milieu = (gau+droite)/2;
        if (tab[milieu]==x)
            return milieu;
        if (tab[milieu]>x)
            droite = milieu-1;
        else
            gau = milieu;
    }
    return -1;
}

int recherche(int tab[],int x,int size) {
    return rechercheBinaire(tab,x,0,size-1);
}

int main(int argc, char *argv[])
{
    int *a;
    int i;

    // (int *) est un cast. indispensable ?
    a = (int *)malloc((argc - 2) * sizeof(int));

    for (i = 0; i < argc - 2; i++)
        a[i] = atoi(argv[i + 1]);

    int val = atoi(argv[i + 1]);

    int trouve = recherche(a, val, argc - 1);
    if (trouve!=-1)
        printf("la valeur %i est à l'indice %i",val,trouve);
    else
        printf("valeur %i pas trouvée",val);
    free(a);
    return 0;
}