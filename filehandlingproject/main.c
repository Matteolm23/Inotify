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

#include "dir_file_functions.h"
#include "inotify_functions.h"

#define PATH_MAX 4096

int main(void)
{
    char path[PATH_MAX];
    int choice = 0;

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
        printf(
            "\nScegli un'opzione:\n\n"
            " 1. Monitoraggio della directory \n"
            " 2. Lista dei contenuti della directory\n"
            " 3. Pulisci lo schermo\n"
            " 4. Crea file\n"
            " 5. Crea directory\n"
            " 6. Modifica file\n"
            " 7. Visualizza file\n"
            " 8. Elimina file/directory\n"
            " 9. Cambia directory\n"
            "10. Informazioni su file/directory\n"
            "\nPremi Ctrl+C per uscire\n"
        );

        if (scanf("%d", &choice) != 1)
            while(getchar() != '\n')
                continue;
            
        switch(choice)
        {
            default:
                printf("\nComando inesistente\n\n");
                usleep(500000);
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
                create_directory(newpath);
                usleep(500000);
            break;
            case 6:
                modify_file();
                ccontinue = false;
            break;
            case 7:
                view_file();
                usleep(500000);
            break;
            case 8:
                delete_dirfile();
                usleep(500000);
            break;
            case 9:
                printf("inserisci la nuova directory: ");
                scanf("%s", path);
                fflush(stdin);

                newpath = realpath(path,NULL);

                change_directory(newpath);
                usleep(500000);
            break;
            case 10:
                file_info();
                usleep(500000);
            break;
        }
    }
    return 0;
}