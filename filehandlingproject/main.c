#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <sys/inotify.h> 
#include <limits.h>
#include <dirent.h>
#include <stdbool.h>

#include "directory_functions.h"
#include "inotify_functions.h"

#define PATH_MAX 4096

int main(void)
{
    char path[PATH_MAX];
    int choice;

    printf("inserisci la directory iniziale: ");
    scanf("%s", path);
    fflush(stdin);

    char *newpath = realpath(path,NULL);

    if (newpath != NULL)
        printf("\npercorso della directory: %s\n\n", newpath);
    else
    {
        printf("\npercorso inesistente\n\n");
        return 0;
    }

    bool ccontinue = true;

    while( ccontinue == true )
    {
        choice = 0;

        printf("Scegli un'opzione:\n\n");
        printf(
            "1. Monitoraggio della directory \n"
            "2. Lista dei contenuti della directory\n"
            "3. Pulisci lo schermo\n"
            "4. Crea File/directory\n"
            "5. Elimina File/directory\n"
            "6. Cambia directory\n"
            "7. Crea directory\n"
            "\n"
        );

        scanf("%d", &choice);
        
        switch(choice)
        {
            default:
                printf("\nComando inesistente\n\n");
                ccontinue = false;
            break;
            case 1:
                inotify_monitor(newpath);
            break;
            case 2:
                directory_contents(newpath);
                usleep(500000);
            break;
            case 3:
                printf("\033[2J\033[H");
            break;
            case 4:
                create_file();
                usleep(500000);
            break;
            case 5:
                delete_dirfile();
                usleep(500000);
            break;
            case 6:
                printf("inserisci la nuova directory: ");
                scanf("%s", path);
                fflush(stdin);

                newpath = realpath(path,NULL);

                change_directory(newpath);
                usleep(500000);
            break;
            case 7:
                create_directory(newpath);
                usleep(500000);
            break;
        }
    }
    return 0;
}