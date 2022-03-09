#ifndef _UTIL_H_
#define _UTIL_H_
/* ------------------------------------------------------------------------------------
 * Primitives de POSIX.1
 * ------------------------------------------------------------------------------------
 * Jean-Paul Rigault --- ESSI --- Mars 2005
 * d'après une correction d'Erick Gallesio (ESSI)
 */

/*!
 * \file
 *
 * Quelques fonctions utiles pour \b lsrec et \b copy
 */

#include <stdbool.h>

//! Le nom de fichier est-il celui d'un répertoire ?
bool is_dir(const char *filename);

//! Le nom de fichier est-il "." ou ".." ?
bool is_dot_dir(const char *filename);

//! Nom de base d'un fichier */
const char *get_basename(const char *filename);

//! Deux noms de fichiers désignent-ils le même fichier physique ?
bool same_file(const char *fn1, const char *fn2);

//! Tester l'existence d'un fichier
bool file_exists(const char *filename);


#endif // _UTIL_H_ 
