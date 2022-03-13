/* ------------------------------------------------------------------------------------
 * Primitives de POSIX.1
 * ------------------------------------------------------------------------------------
 * Erick Gallesio (2005)
 * Jean-Paul Rigault (2008/11/21)
 * Stéphane Lavirotte (2017/03/17)
 * ------------------------------------------------------------------------------------
 * Un substitut de la commande ls d'Unix (en fait ls -laR). Les fichiers sont affichés
 * dans l'ordre où ils se trouvent dans le répertoire (alors que le vrai ls les trie).
 * ------------------------------------------------------------------------------------
 */

/*!
 * \file
 *
 * Un substitut de la commande \b ls d'Unix (en fait <b>ls -laR</b>).
 *
 * \note Les fichiers sont affichés dans l'ordre où ils se trouvent dans le
 * répertoire (alors que le vrai ls les trie).
 *
 */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <pwd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

/* Pour avoir \c PATH_MAX (on pourrait aussi utiliser pathconf() pour ne pas être
 * lié à Linux)
 */
#include <linux/limits.h>

//! Fonctions utilitaires de manipulation de noms de fichiers
#include "util.h"

/*! Imprimer le type du fichier et les droits d'accès
 *
 * On ne considère ici que deux types de fichiers : ordinaire et
 * répertoire. Les autres sont indiqués par un '?'.
 */
void print_mode(mode_t mode)
{
    char buff[] = "drwxrwxrwx";
    char *p = buff;

    if (S_ISREG(mode))
        *p = '-';    	// enlever le 'd' si nécessaire
    else if (!S_ISDIR(mode))
        *p = '?';

    for (++p; *p != '\0'; ++p, mode <<= 1)
        if (!(mode & S_IRUSR))
            * p = '-'; // enlever 'r' 'w' ou 'x' suivant le cas

    printf("%s", buff);
}

//! Formattage d'une date grâce à \c strftime()
char *format_date(time_t t)
{
    struct tm *date;
    static char buffer[30];

    date = localtime(&t);
    strftime(buffer, 30, "%d/%m/%Y %H:%M", date);
    return buffer;
}

//! Impression de la ligne correspondant à une entrée
void print_fileinfo(const char *filename)
{
    struct stat st;
    struct passwd *pass;
    char *owner;

    // Recherche des attributs du fichier
    if (stat(filename, &st) == -1) {
        fprintf(stderr, "stat() impossible sur %s\n", filename);
        return;
    }

    // Recherche du nom du propriétaire
    pass = getpwuid(st.st_uid);
    owner = pass ? pass->pw_name : "INCONNU";


    // Impression des protections
    print_mode(st.st_mode);

    // Impression des infos complémentaires
    printf(" %3zu %-8s %7zu %s %s\n",
           st.st_nlink, // Nombre de liens
           owner,       // Nom en clair
           st.st_size,  // taille en octets
           format_date(st.st_mtime), // date de modif
           get_basename(filename)); // Nom de base du fichier
}

//! Lister les infos d'un fichier ou d'un répertoire
void list(const char *filename)
{
    DIR *dirp;
    struct dirent *dentry;
    char name[PATH_MAX + 1];

    if (is_dir(filename)) {
        // Nous avons affaire à un répertoire
        if ((dirp = opendir(filename)) == NULL)
            fprintf(stderr, "répertoire %s illisible\n", filename);
        else {
            // On imprime le nom du répertoire visité
            printf("%s:\n", filename);

            // 1ere phase: lister tout le monde
            while ((dentry = readdir(dirp)) != NULL) {
                snprintf(name, PATH_MAX + 1, "%s/%s", filename, dentry->d_name);
                print_fileinfo(name);
            }

            // 2nde phase: appel récursif pour les sous-répertoires de filename
            rewinddir(dirp);
            while ((dentry = readdir(dirp)) != NULL) {
                // On évite "." et ".." (sinon boucle infinie !)
                if (!is_dot_dir(dentry->d_name)) {
                    snprintf(name,  PATH_MAX + 1, "%s/%s", filename, dentry->d_name);
                    if (is_dir(name))
                        list(name);
                }
            }
            closedir(dirp);
        }
    } else
        print_fileinfo(filename);
}

/*! Programme principal
 *
 * Invocation : lsrec.exe [file ...]
 *
 * Sans argument on liste le répertoire courant, sinon on liste (récursivement)
 * tous les fichiers donnés en argument.
 */
int main(int argc, char **argv)
{
    if (argc == 1)
        list(".");
    else {
        while (*++argv)
            list(*argv);
    }
    return 0;
}

