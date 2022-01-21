/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Tahmid Sajin 500 830 210, EE Username: tsajin, COE628 Section 2, Lab 3
 *
 * Created on February 1, 2021, 06:39 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/*
 * 
 */
int main(int argc, char** argv) {
    while (1) {
        clock_t current = clock();
        while (clock() < current + 500);
        
        printf("Your Command >");
        char ch;
        char *array = malloc(sizeof (char*)*100);
        
        while ((ch = getchar()) != '\n') {
            int len = strlen(array);
            array[len] = ch;
            array[len + 1] = '\0';
        }
        
        char *process = strtok(array, " ");
        char **r = NULL;
        int i = 0;
        
        while (process) {
            r = realloc(r, sizeof (char*)*++i);
            r[i - 1] = process;
            process = strtok(NULL, "\0");
        }
        
        r = realloc(r, sizeof (char*) * (i + 1));
        
        if (array[strlen(array) - 1] == '&') {
            array[strlen(array) - 1] = '\0';
            
            if (fork() == 0) {
                printf("Created the child process\n");
                execvp(array, r);
            }
        } else {
            if (fork() == 0) {
                printf("Created the child process\n");
                execvp(array, r);
            } else {
                printf("Parent process waiting\n");
                wait(NULL);
                printf("Parent process ends\n");
            } if (array[strlen(array) - 1] == '&') {
                array[strlen(array) - 1] = '\0';
                
                if (fork() == 0) {
                    printf("Created the child process\n");
                    execvp(array, r);
                }
            }
        }
    }

    return (EXIT_SUCCESS);
}

