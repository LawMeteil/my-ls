#ifndef FOO_H_
#define FOO_H_

#include <stdio.h>
#include <unistd.h>

int option(int ac, char *av[]){
    int opt;

    while ((opt = getopt(ac, av, "lRrdtaAL")) != -1) {
        switch (opt) {
        case 'l':
        printf("option l\n");
            break;

        case 'R':
        printf("option R\n");
            break;

        case 'r':
        printf("option r\n");
            break;

        case 'd':
        printf("option d\n");
            break;

        case 't':
        printf("option t\n");
            break;

        case 'a':
        printf("option a\n");
            break;

        case 'A':
        printf("option A\n");
            break;

        case 'L':
        printf("option L\n");
            break;
            
        default:
            break;
        
        }
    }
    return (0);
}

#endif