#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>
#include <dirent.h>
#include <sys/stat.h>

#define NORMAL "\x1b[0m"
#define CYAN "\x1b[36m"
#define GREEN "\x1b[32m"
#define RED "\x1b[31m"

int main()
{
    char command[50];
    char host[30];
    char path[666];
    char *c , *p , *args[50];
    struct stat st = {0};

    while(true) {
        /* tokenizer */
        getcwd(path, sizeof(path));
        gethostname(host, sizeof(host));
        printf("%s%s@%s:~%s%s$ ", GREEN, getenv("USER"), host, NORMAL, path);
        fgets(command, sizeof(command), stdin);
        command[strlen(command) - 1] = '\0';
        p = strtok(command, " ");
        int i = 0;

        while (p != NULL) {
            args[i] = p;
            i++;
            p = strtok(NULL, " ");
        }
        c = args[0];
        args[i] = NULL;

        if (strcmp(c, "cd") == 0) {
            if (args[1] == NULL) {
                chdir("/home");
            }

            else {
                chdir(args[1]);
            }
        }

        else if (strcmp(c,"pwd")==0){
            printf("%s\n", path);
        }

        else if (strcmp(c,"sleep")==0) {
            if (args[1] == NULL) {
                printf("%s Nie podano argumentu %s\n", RED, NORMAL);
            }
            else {
                sleep(atoi(args[1])); }
        }


        else if(strcmp(c, "mkdir")==0) {
            if (args[1] == NULL){
                printf("%s Nie podano nazwy tworzonego folderu%s\n", RED, NORMAL);
            }
            else (stat(args[1], &st) == -1); {
                mkdir(args[1], 0777);
            }
        }

        else if (strcmp(c, "exit") == 0) {
            exit(EXIT_SUCCESS);
        }

        else if (strcmp(c, "clear") == 0) {
            printf("\033[H\033[J");
        }

        else if (strcmp(c, "help") == 0) {
            printf("-----------------------------\n"
                   "|       %s Microshell %s        |\n"
                   "|                           |\n"
                   "|     Stworzony przez:      |\n"
                   "|                           |\n"
                   "|   Arkadiusza Kowalskiego  |\n"
                   "|                           |\n"
                   "|     dostepne komendy:     |\n"
                   "|                           |\n"
                   "|    pwd, cd, sleep, mkdir  |\n"
                   "|                           |\n"
                   "|        exit, clear        |\n"
                   "-----------------------------\n", CYAN, NORMAL);
        }

        else {
            printf("%s Komenda wywolana spoza shella%s\n", RED, NORMAL);
            int pid =fork();
            if (pid>0)
                wait(NULL);
            if (pid==0){
                execvp(command, args);
            }
        }
    }
}
