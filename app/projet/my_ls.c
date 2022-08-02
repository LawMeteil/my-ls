#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <errno.h>

//Gestion del'affichage
//Remplace le printf
void my_putchar(char c){
    write(1, &c, 1);
}
//Affiche en str
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
//Fin de la gestion del'affiche

int my_strcmp(const char *s1, const char *s2)
{
    int i = 0;
    int j = 0;

    while((s1[i] != '\0' && s2[j] != '\0') && s1[i] == s2[j])
        {
            i++;
            j++;
        }
    if (s1[i] == s2[j])
        {
            return 0;
        }
    else
        {
            return s1[i] - s2[j];
        }
}

void *my_strcpy(char *dest, const char *src)
{
    int i = 0;

    while(src[i] != '\0')
        {
            dest[i] = src[i];
            i++;
        }
    dest[i] = '\0';

    return dest;
}

//Tableau des permission de test7.c
void permission( mode_t filemode, char str[] ) {
 
    my_strcpy( str, "----------" );
    if( S_ISREG( filemode ) ) str[0] = '-';
    if( S_ISDIR( filemode ) ) str[0] = 'd';
    if( S_ISLNK( filemode ) ) str[0] = 'l';

    //Permission utilisateurs
    if( filemode & S_IRUSR ) str[1] = 'r';
    if( filemode & S_IWUSR ) str[2] = 'w';
    if( filemode & S_IXUSR ) str[3] = 'x';

    //Permission groupes
    if( filemode & S_IRGRP ) str[4] = 'r';
    if( filemode & S_IWGRP ) str[5] = 'w';
    if( filemode & S_IXGRP ) str[6] = 'x';
 
    //Permission autres groupes
    if( filemode & S_IROTH ) str[7] = 'r';
    if( filemode & S_IWOTH ) str[8] = 'w';
    if( filemode & S_IXOTH ) str[9] = 'x';
}

//Date des fichiers et dossiers
void time_show(time_t filetime){
    struct tm* timeinfo;
    timeinfo = localtime( &filetime );
    char buffer[80];
    strftime(buffer, 80, "%b %d %H:%M ", timeinfo);
    my_putstr(buffer);
}

void my_ls(DIR *dir,int op_a,int op_l){
    struct dirent *dirent;
    struct stat sb;
    
    while ((dirent = readdir(dir)) != NULL)
    { 
        stat(dirent->d_name, &sb);
        mode_t mode = sb.st_mode;
        // mode_t mode = statinfo.st_mode;
        if (op_a == 0 && dirent->d_name[0] == '.')
        {
			continue;
        }
        else if ((dirent->d_name[1] == '\0' || (my_strcmp(dirent->d_name, "..") == 0)) && op_a == 2 )
        {
            continue;
        }
        //test.c et test5.c ready
        // option -l
        if(op_l == 1){
             char str[0];
            permission(mode, str);
            my_putstr(str);
            my_putchar(' ');
            my_putstr(getpwuid(sb.st_uid)->pw_name);
            my_putchar(' ');
            my_putstr(getgrgid(sb.st_gid)->gr_name);
            my_putchar(' ');
            my_putnbr(sb.st_size);
            my_putstr("\t");
            time_show(sb.st_mtime);
        }
    my_putstr(dirent->d_name);
    my_putchar('\n');
    }
}

int main(int ac, char *av[]){
    
    DIR *dir;
    char *dh = ".";
    dir = opendir(dh);
    int op_a = 0;
    int op_l = 0;
    
    if (ac == 1){
        my_ls(dir, op_a, op_l);
    }
    
   else
    {
        int i = 1;
        while (i < ac)
        {
            if (av[i][0] == '-')
            {
                if (av[i][1] == 'a')
                op_a = 1;
                else if (av[i][1] == 'l')
                op_l = 1;
            }
            else
            {
                if ((dir = opendir(av[i])) == NULL)
                {
			        //Erreur
			        my_putstr("my_ls: cannot access '");
                    my_putstr(av[i]);
                    my_putstr("': No such file or directory \n");
                    return 1;
                }
                dir = opendir(av[i]);
            }
             i++;
        }
        my_ls(dir, op_a, op_l);
    }
	return 0;
}
