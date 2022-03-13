/* ------------------------------------------------------------------------------------
 * Primitives de POSIX.1
 * ------------------------------------------------------------------------------------
 * Jean-Paul Rigault --- ESSI --- Mars 2005
 * d'après une correction d'Erick Gallesio (ESSI)
 * $Id: util.c,v 1.2 2008/04/21 18:08:09 jpr Exp $
 * ------------------------------------------------------------------------------------
 * Quelques fonctions utiles pour lsrec et copy
 * ------------------------------------------------------------------------------------
 */

/*!
 * \file
 *
 * Quelques fonctions utiles pour \b lsrec et \b copy
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

#include "util.h"

bool is_dir(const char *filename)
{
    struct stat st;
    return stat(filename, &st) ? 0 : S_ISDIR(st.st_mode);
}

bool is_dot_dir(const char *filename)
{
    return (filename[0] == '.')
           && (filename[1] == '\0' || (filename[1] == '.' && filename[2] == '\0'));
}

const char *get_basename(const char *filename)
{
    const char *b = strrchr(filename, '/'); // recherche du dernier car. '/'
    return (b == NULL) ? filename : (b + 1);
}

//! Do \a fn1 and \a fn2 dzsignate the same file?
bool same_file(const char *fn1, const char *fn2)
{
    struct stat fn1st;
    struct stat fn2st;

    if (stat(fn1, &fn1st) || stat(fn2, &fn2st))
        return 0;

    //Les deux fichiers existent. Ils sont identiques s'ils ont le même i-numéro
    //(st_ino) et résident dans le même système de fichiers (st_dev)
    return fn1st.st_dev == fn2st.st_dev && fn1st.st_ino == fn2st.st_ino;
}

bool file_exists(const char *filename)
{
    struct stat st;

    return !stat(filename, &st);  // peut etre un peu simpliste (ENOENT ?)
}
