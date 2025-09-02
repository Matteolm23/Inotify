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

#define MAX_EVENT_MONITOR 2048
#define NAME_LEN 32
#define MONITOR_EVENT_SIZE (sizeof(struct inotify_event))
#define BUFFER_LEN MAX_EVENT_MONITOR*(MONITOR_EVENT_SIZE+NAME_LEN)

void inotify_monitor(char *path)
{
    int fd, wd;
    char buffer[BUFFER_LEN];

    fd = inotify_init();
    if (fd < 0)
    {
        printf("Inotify not initialized");
        return;
    }

    wd = inotify_add_watch(fd, path, IN_CREATE | IN_DELETE | IN_MODIFY | IN_MOVED_FROM | IN_MOVED_TO );

    if(wd == -1)
    {
        printf("Non e' stato possibile monitorare la directory %s", path);
        return;
    }
    else
        {printf("\nMonitorando la directory %s...\nPremi Ctrl+C per uscire dal programma\n", path);}

    int i = 0;
    fflush(stdout);

    while(1)
    {
        i = 0;
        int totalread = read(fd,buffer,BUFFER_LEN);

        if (totalread < 0)
            printf("errore di lettura");

        while(i < totalread)
        {
            struct inotify_event *event = (struct inotify_event*)&buffer[i];
            
            if(event -> len)
            {
                if(event -> mask & IN_CREATE)
                {
                    if(event -> mask & IN_ISDIR)
                        {printf("e' stata creata la cartella '%s'\n", event->name);}
                    else
                        {printf("e' stato creato il file '%s'\n", event->name);}
                }

                if(event -> mask & IN_MODIFY)
                {
                    if(event -> mask & IN_ISDIR)
                        {printf("la cartella '%s' e' stata modificata\n", event->name);}
                    else
                        {printf("il file '%s' e' stato modificato\n", event->name);}
                }

                if(event -> mask & IN_DELETE)
                {
                    if(event -> mask & IN_ISDIR)
                        {printf("la cartella '%s' e' stata eliminata\n", event->name);}
                    else
                        {printf("il file '%s' e' stato eliminato\n", event->name);}
                }   

                if(event -> mask & IN_MOVED_FROM)
                {
                    if(event -> mask & IN_ISDIR)
                        {printf("la cartella '%s' e' stata spostata fuori dalla directory '%s'\n", event->name, path);}
                    else
                        {printf("il file '%s' e' stato spostato fuori dalla directory '%s'\n", event->name, path);}
                }   

                if(event -> mask & IN_MOVED_TO)
                {
                    if(event -> mask & IN_ISDIR)
                        {printf("la cartella '%s' e' stata spostata nella directory '%s'\n", event->name, path);}
                    else
                        {printf("il file '%s' e' stato spostato nella directory '%s'\n", event->name, path);}
                }   
                
                i += MONITOR_EVENT_SIZE+event->len;
            }
        }
    }

    inotify_rm_watch(fd,wd);
    close(fd);
}