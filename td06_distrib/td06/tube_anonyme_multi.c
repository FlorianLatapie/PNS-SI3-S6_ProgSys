/*
Quand on utilise un tube, on n’est pas limité à un seul écrivain ou un seul lecteur. Ecrire un programme tube_ano-
nyme_multi.exe qui aura deux fils qui écriront dans le tube et le père qui lira les données. Les deux fils écrivent
respectivement l’alphabet l’un en majuscule (« ABCD…YZ ») et l’autre en minuscule (« abcd…yz »). Les écritures se
feront 2 caractères par 2 caractères et une pause d’une seconde sera faite entre deux écritures par chacun des fils. Le
père tentera de lire 3 caractères au maximum dès que possible.
Modifiez le temps pour que le premier fils écrive toutes les 1 secondes alors que le second écrira toutes les 2 secondes.
*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define alphabet "abcdefghijklmnopqrstuvwxyz"
#define ALPHABET "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

void lecture(int fd)
{
    // lis charactère par charactère le descripteur de fichier et l'afficher dans la sortie standard
    char buff[1];
    while (read(fd, buff, 1))
    {
        write(STDOUT_FILENO, buff, sizeof(buff));
    }
    printf("\n");
}

void ecriture(int descripteurFichier, char *string, int tempsAttente)
{
    // écris 2 charactères par 2 charactères dans le descripteur de fichier en attendant le temps d'attente
    while (*string)
    {
        write(descripteurFichier, string, 2);
        sleep(tempsAttente);
        string += 2;
    }
    close(descripteurFichier);
}

int main()
{
    int p[2];
    pipe(p);
    switch (fork())
    {
    case -1:
        perror("Erreur fork");
        abort();
    case 0:
        ecriture(p[1], alphabet, 1);
        close(p[1]);
        break;
    default:
        switch (fork())
        {
        case -1:
            perror("Erreur fork");
            abort();
        case 0:
            close(p[0]);
            ecriture(p[1], ALPHABET, 2);
            close(p[1]);
            break;
        default:
            close(p[1]);
            lecture(p[0]);
            close(p[0]);
            break;
        }
    }
    return 0;
}
