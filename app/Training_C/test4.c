#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>
#include <pwd.h>

void my_ls(DIR *dir, int ac, char *av[]){
    

}

int main(int ac, char *av[]){
    DIR *dir;
    struct dirent *dirent;
    struct stat sb;
    char *name = (ac < 2) ? "." : av[1];

    int opt;
    while ((opt = getopt(ac, av, "lRrdtaAL")) != -1) {
        switch (opt) {
        case 'l':
    while ((dirent = readdir(dir)) != NULL) {
        if (dirent->d_name[0] != '.') {
            stat(dirent->d_name, &sb);
            printf("%s %s %lld %ld\n", dirent->d_name, getpwuid(sb.st_uid)->pw_name, sb.st_size, sb.st_nlink);
        }
    }
        // printf("%s %s %lld %ld\n", dirent->d_name, getpwuid(sb.st_uid)->pw_name, sb.st_size, sb.st_nlink);
            break;

        case 'R':
        printf("option R\n");
            break;

            default:
                break;
        }
    }

    if ((dir = opendir(name)) == NULL) {
        printf("my_ls: you don't open '%s'\n", name);
        return (1);
    }


    my_ls(dir,ac,av);

    closedir(dir);

    return (0);
}
