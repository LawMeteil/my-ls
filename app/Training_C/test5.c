#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>


void my_putchar(char c){
    write(1, &c, 1);
}

void my_putstr(const char *str)
{
    while (*str != '\0'){
        my_putchar(*str);
        str++;
    }
}

//Passe de str à int
void my_putnbr(long int n){
    long int m = n;
    if (m < 0){
        m = -1 * m;
        my_putchar('-');
    }
    if ((m / 10) > 0)
    {
        my_putnbr(m / 10);
    }
    my_putchar(m % 10 + '0');
}

//Date des fichiers et dossiers
void time_show(time_t filetime){
    struct tm* timeinfo;
    timeinfo = localtime( &filetime );
    char buffer[80];
    strftime(buffer, 80, "%b %d %H:%M ", timeinfo);
    my_putstr(buffer);
}

void permission( mode_t filemode, char str[] ) {
 
    my_strcpy( str, "----------" );
    if( S_ISREG( filemode ) ) str[0] = '-';
    if( S_ISDIR( filemode ) ) str[0] = 'd';
    if( S_ISLNK( filemode ) ) str[0] = 'l';

    //User permission bit
    if( filemode & S_IRUSR ) str[1] = 'r';
    if( filemode & S_IWUSR ) str[2] = 'w';
    if( filemode & S_IXUSR ) str[3] = 'x';

    //Group permission bit
    if( filemode & S_IRGRP ) str[4] = 'r';
    if( filemode & S_IWGRP ) str[5] = 'w';
    if( filemode & S_IXGRP ) str[6] = 'x';
 
    //Other group permission bits
    if( filemode & S_IROTH ) str[7] = 'r';
    if( filemode & S_IWOTH ) str[8] = 'w';
    if( filemode & S_IXOTH ) str[9] = 'x';
}

void my_ls(DIR *dir){
    struct dirent *dirent;
    struct stat sb;

    while ((dirent = readdir(dir)) != NULL) {
        if (dirent->d_name[0] != '.'){
            stat(dirent->d_name, &sb);
            // write(1, dirent->d_name, sizeof(dirent));
            // write(1, getpwuid(sb.st_uid)->pw_name, sizeof(dirent));
            // // write(1, sb.st_size, sizeof(dirent));
            my_putstr(dirent->d_name);
            my_putstr("\t");
            my_putstr("user:");
            my_putchar(' ');
            my_putstr(getpwuid(sb.st_uid)->pw_name);
            my_putstr("\t");
            my_putchar(' ');
            my_putstr("grp:");
            my_putstr(getgrgid(sb.st_gid)->gr_name);
            my_putchar(' ');
            my_putnbr(sb.st_size);
            my_putstr("\t");
            // printf(sb.st_nlink);
            // printf(ctime(&sb.st_mtime));
            my_putstr("\n");
        }
    }
}

int main(int ac, char *av[]){
    DIR *dir;
    char *name = (ac < 2) ? "." : av[1];
    dir = opendir(name);

    char optstring[]="a";
    int c;

    if ((c=getopt (ac, av, optstring)) != EOF)
    {
        my_putstr("a");
    }
    

    my_ls(dir);

    closedir(dir);

    return 0;
}