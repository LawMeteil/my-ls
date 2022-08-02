#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <stdlib.h>

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

char *my_strcpy(char *dest, const char *src)
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


void my_putchar(char c)
{
  write(1, &c, 1);
}

void my_putstr(char *str)
{
    int j;
    j = 0;
    while (str[j] != '\0')
    {
    my_putchar(str[j]);
    j++;
    }
}

void mode_to_letters( mode_t filemode, char str[] ) {
 
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

char* uid_to_name( uid_t uid ){
    return getpwuid( uid )->pw_name;
}

char* gid_to_name( gid_t gid ){
    return getgrgid( gid )->gr_name;
}

void show_time(time_t filetime)
{
    struct tm* ptm;
    ptm = localtime( &filetime );
    char buffer[80];
    strftime(buffer, 80, "%b  %d %H:%M ", ptm);
    my_putstr(buffer);
}

void my_putnbr(long int n)
{
    long int m = n;
    if ( m < 0 )
        {
            m = -1 * m;
            my_putchar('-');
        }
    if ((m / 10) > 0 )
        {
            my_putnbr(m / 10);
        }
    my_putchar(m % 10 + '0');
}

void option_a(DIR *dh,int op_a, int op_l)
{
    struct dirent *d;
    struct stat statinfo;
    
    while ((d = readdir(dh)) != NULL)
    { 
        stat(d->d_name, &statinfo);
        mode_t mode = statinfo.st_mode;
        if (op_a == 0 && d->d_name[0] == '.')
        {
			continue;
        }
        else if ((d->d_name[1] == '\0' || (my_strcmp(d->d_name, "..") == 0)) && op_a == 2 )
        {
            continue;
        }
        
        if (op_l == 1)
        {
            char str[10];
            mode_to_letters(mode, str);
            my_putstr(str);
            my_putchar(' ');
            my_putnbr(statinfo.st_nlink);
            my_putchar('\t');
            my_putstr(uid_to_name(statinfo.st_uid));
            my_putchar(' ');
            my_putstr(gid_to_name(statinfo.st_gid));
            my_putchar(' ');
            my_putnbr(statinfo.st_size);
            my_putchar('\t');
            show_time(statinfo.st_mtime);
        }
        my_putstr(d->d_name);
        my_putchar('\n');
    }
}

int main(int argc, char *argv[])
{
    DIR *dh;
    char *dir = ".";
    dh = opendir(dir);
    int op_a = 0;
    int op_l = 0;

    if (argc == 1)
	{
		option_a(dh, op_a, op_l);
	}
    else
    {
        int i = 1;
        while (i < argc)
        {
            if (argv[i][0] == '-')
            {
                if (argv[i][1] == 'a')
                op_a = 1;
                else if (argv[i][1] == 'A')
                op_a = 2;
                else if (argv[i][1] == 'l')
                op_l = 1;
            }
            else
            {
                if ((dh = opendir(argv[i])) == NULL)
                {
			        //If the directory is not found
			        my_putstr("my_ls: cannot access '");
                    my_putstr(argv[i]);
                    my_putstr("': No such file or directory \n");
                    return 1;
                }
                dh = opendir(argv[i]);
            }
             i++;          
        }
        option_a(dh, op_a, op_l);
    }
	return 0;
}