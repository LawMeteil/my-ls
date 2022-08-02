#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
   int option;
   while((option = getopt(argc, argv, ":if:lrx")) != -1){ 
      switch(option){
         case 'i':
         case 'l':
         case 'r':
            printf("Given Option: %c\n", option);
            break;
         case 'f':
            printf("Given File: %s\n", optarg);
            break;
         case ':':
            printf("option needs a value\n");
            break;
         case '?': 
            printf("unknown option: %c\n", optopt);
            break;
      }
   }
}