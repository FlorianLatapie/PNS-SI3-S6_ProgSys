#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>

void print_fileinfo(const char *filename)
{
    printf("%s ", get_basename(filename));
}

void list(const char *filename)
{
    if (is_dir(filename))
    {
        char buffer[PATH_MAX];

        struct dirent *dentry;
        DIR *dirp = opendir(filename);

        printf("%s:\n", filename);

        if (dirp == NULL)
        {
            perror("Répertoire inaccessible\n");
            exit(EXIT_FAILURE);
        }

        while ((dentry = readdir(dirp)) != NULL)
        {
            print_fileinfo(dentry->d_name);
        }

        printf("\n\n");

        rewinddir(dirp);

        while ((dentry = readdir(dirp)) != NULL)
        {
            if (!is_dot_dir(dentry->d_name))
            {
                snprintf(buffer, PATH_MAX, "%s/%s", filename, dentry->d_name);
                list(buffer);
            }
        }
        closedir(dirp);
    }
}

int main(int argc, char const *argv[])
{
    if (argc == 1)
    {
        list(".");
    }
    else
    {
        while (*++argv)
        {
            list(*argv);
        }
    }

    return 0;
}
