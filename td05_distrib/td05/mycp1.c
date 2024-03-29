#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include "util.h"
#include <stdlib.h>

#define MAX 1000

void copy(const char* source, const char* destination){
    int fichierSource = open(source, O_RDONLY);
    int fichierDestination = open(destination, O_WRONLY | O_CREAT);
    
    if ((fichierSource == -1) ||(fichierDestination == -1)){
        exit(1);
    }

    char buffer[MAX];

    int n;
    while ((n = read(fichierSource, buffer, MAX)) != 0){
        write(fichierDestination, buffer, n);
    }
    
    close(fichierSource);
    close(fichierDestination);
}

int main(int argc, char const *argv[])
{
    assert(argc>=3);

    if (argc == 3){
        copy(argv[1], argv[2]);
    } else {
        const char* dossier = argv[argc-1];

        if (!is_dir(dossier)){
            exit(1);
        }
        for (int i = 1; i<argc-1 ; i++){
            if (is_dir(argv[i]) || !file_exists(argv[i])){
                exit(1);
            }
            char buf[MAX];
            snprintf(buf, MAX, "%s/%s", dossier, get_basename(argv[i]));
            copy(argv[i], buf);
        }
    }
    
    return 0;
}
