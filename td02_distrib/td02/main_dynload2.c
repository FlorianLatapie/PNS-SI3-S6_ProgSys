#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "sort.h"
#include "utils.h"
#include "timer.h"
#include "load_library.h"
#include <string.h>

/* ------------------------------------------------------------------------------------
 * Valeurs par défaut des variables globales qui suivent 
 * ------------------------------------------------------------------------------------
 */

#define SIZE 10000
#define FALSE 0
#define TRUE 1

/* ------------------------------------------------------------------------------------
 * Variables globales 
 * ------------------------------------------------------------------------------------
*/

static int Size_Array = SIZE;
static int Verbose = TRUE;

/* ------------------------------------------------------------------------------------
 * Prototypes de fonctions définies plus tard 
 * ------------------------------------------------------------------------------------
*/
static void Scan_Args(int argc, char *argv[]);
static void Usage(const char *execname);

int main(int argc, char *argv[])
{
    /* Décodage des arguments de la ligne de commande */
    Scan_Args(argc, argv);
    char** lib_names = malloc(4 * sizeof(char *));
    
     if (!lib_names) {
        fprintf(stderr, "memory allocation failed (malloc)");
        exit(EXIT_FAILURE);
    }

    lib_names[0] = "libTri_bubble-dynamicLib.so";
    lib_names[1] = "libTri_insertion-dynamicLib.so";
    lib_names[2] = "libTri_merge-dynamicLib.so";
    lib_names[3] = "libTri_quick-dynamicLib.so";
    int list[Size_Array];

    // Initialize a ramdom list of numbers;
    srand(0);
    for (int i = 0; i < Size_Array; i++) {
        list[i] = rand() % 1000;
    }

	if (Verbose) {
		printf("Array to sort:");
		print_list(list, Size_Array);
	}
	
   
    for (int i = 0; i < 4; i++)
    {
        load_library(lib_names[i]);
        struct timespec vartime = timer_start();
        sort_from_lib(list, Size_Array);
        long time_elapsed_nanos = timer_end(vartime); 
        if (Verbose){
            printf("Time taken for sorting (nanoseconds): ");
            printf("%ld\n", time_elapsed_nanos);
        }

        unload_library(); 
    }
	
  
	if (Verbose) {
		printf("Sorted array:");
		print_list(list, Size_Array);
	}
}

/* Analyse des arguments 
 * ----------------------
 */
static void Scan_Args(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            switch (argv[i][1]) {
            case 'h':
                Usage(argv[0]);
                exit(1);
            case 's':
                Size_Array = atoi(argv[++i]);
                break;
			case 'v':
				Verbose = TRUE;
				break;
            }
        } 
    }
}

/* Information d'utilisation
 * -------------------------
 */
static void Usage(const char *execname)
{
    fprintf(stderr, "\nUsage: %s [options]\n", execname);
    fprintf(stderr, "\nOptions générales\n"
           "-----------------\n"
           "-h\tce message\n"
           "-s\ttaille du tableau à trier\n"
		   "-v\taffiche plus d'informations\n");
}