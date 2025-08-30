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

#define MAX_FILENAME_LENGTH 1024

void directory_contents(char *path) 
{
    DIR *folder;
    struct dirent *entry;
    int files = 0;

    folder = opendir(path);

    if(folder == NULL)
    {
        printf("Non e' stato possibile leggere la directory");
        return;
    }

    printf("\n");
    while( (entry=readdir(folder)) )
    {
        files++;
            
        if (files > 2)
            printf("%3d. %s\n",files-2,entry->d_name);
        
    }
    printf("\n");

    closedir(folder);
}

void create_file() 
{
    char name[MAX_FILENAME_LENGTH];
    printf("Inserisci il nome del file da creare: ");
    scanf("%s", name);
    fflush(stdin);

    FILE *fp = fopen(name, "w");
    if (fp != NULL)
    {
        printf("File '%s' creato con successo.\n", name);
        fclose(fp);
    } 
    else
        printf("Errore nella creazione del file");
}

void delete_dirfile() 
{
    char name[MAX_FILENAME_LENGTH];
    printf("Inserisci il nome del file o della directory vuota da eliminare: ");
    scanf("%s", name);
    fflush(stdin);

    struct stat st;

    if (stat(name, &st) == 0) 
    {
        if S_ISDIR(st.st_mode)
        {
            if (remove(name) == 0)
                printf("La directory '%s' e' stata eliminata con successo\n", name);
            else
                printf("Non e' stato possibile eliminare la directory\n");
        }
        else if S_ISREG(st.st_mode)
        {
            if (remove(name) == 0)
                printf("Il file '%s' e' stato eliminato con successo\n", name);
            else
                printf("Non e' stato possibile eliminare il file\n");
        }
    }
    else
    {
        printf("L'elemento non esiste\n"); 
        return;
    }

}

void change_directory(char *path) 
{
    if (chdir(path) == 0)
        printf("la directory e' stata cambiata con successo a '%s'\n", path);
    else
        printf("percorso inesistente\n");
}

void create_directory(char *path)
{

    char name[MAX_FILENAME_LENGTH];
    printf("inserisci il nome della directory da creare: ");
    scanf("%s", &name);
    fflush(stdin);

    realpath(name, NULL);

    if (mkdir(name, 0700) == 0)
        printf("la directory '%s' e' stata creata con successo \n", &name);
    else   
        printf("non e' stato possibile creare la directory\n");
    
}