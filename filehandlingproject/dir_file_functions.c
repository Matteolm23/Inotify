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

#define BUFFER_SIZE 4096
#define MAX_FILENAME_LENGTH 1024

void directory_contents(char *path) 
{
    DIR *folder;
    struct dirent *entry;
    int files = 0;

    folder = opendir(path);

    if(folder == NULL)
    {
        printf("Non e' stato possibile leggere la directory\n");
        return;
    }

    printf("\n---|directory: %s |-----------------------------------\n", path);
    while( (entry=readdir(folder)) )
    {
        files++;
            
        if (files > 2)
            printf("%3d. %s\n",files-2,entry->d_name);
        
    }
    printf("-------------------------------------------------------------------\n");

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
        printf("Errore nella creazione del file\n");
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

void modify_file()
{
    char name[MAX_FILENAME_LENGTH];
    char mode;
    printf("inserisci il nome del file da modificare: ");
    scanf("%s", &name);
    fflush(stdin); 
        
    printf("inserisci 'a' se vuoi scrivere sul file, 'w' se lo vuoi sovrascrivere: ");
    scanf(" %c", &mode);
    getchar();

    FILE *f = fopen(name, (mode == 'a' || mode == 'A') ? "a" : "w");

    if (f != NULL)
    {
        if (mode == 'a' || mode == 'w' || mode == 'A' || mode == 'W' )
            printf("file aperto con successo. Premi Ctrl+D per uscire\n");
        else
        {
            printf("Comando inesistente\n");
            fclose(f);
            return;
        }
    }
    else
    {
        printf("Errore nell'apertura del file per la scrittura\n");
        return;
    }

    char content[BUFFER_SIZE];

    printf("-------------------------------------------------------------\n");
    while (fgets(content, sizeof(content), stdin) != NULL)
        fputs(content, f);

    fflush(stdin);

    printf("\nContenuto scritto nel file '%s' con successo.\n", name); 
    fclose(f);
}

void view_file()
{
    char name[MAX_FILENAME_LENGTH];
    printf("inserisci il nome del file da visualizzare: ");
    scanf("%s", name);
    fflush(stdin); 

    FILE *f = fopen(name, "r");  

    if (f == NULL)
    {
        printf("non e' stato possibile aprire il file\n"); 
        return;
    }

    char ch;
    printf("\n----|file: %s |-----------------------------------\n", name);
    while ((ch = fgetc(f)) != EOF) 
        putchar(ch);

    printf("\n--------------------------------------------------\n");

    fclose(f);
}

void file_info() {
    char name[MAX_FILENAME_LENGTH];
    printf("Inserisci il nome del file/directory: ");
    scanf("%s", name);
    fflush(stdin);

    struct stat file_stat;

    if (stat(name, &file_stat) == 0) 
    {
        printf("\n----|Informazioni su '%s'|--------------------------\n", name);
        printf("Dimensione: %ld byte\n", file_stat.st_size);

        if (S_ISREG(file_stat.st_mode))
            printf("Tipo: file\n");
        else if (S_ISDIR(file_stat.st_mode))
            printf("Tipo: directory\n");

        printf("Permessi: %o\n", file_stat.st_mode & 0777);
        printf("Ultimo accesso: %s", ctime(&file_stat.st_atime));
        printf("Ultima modifica: %s", ctime(&file_stat.st_mtime));
         printf("-------------------------------------------------------------\n", name);
    } 
    else
        printf("Errore nell'ottenere informazioni sul file/directory");
}
