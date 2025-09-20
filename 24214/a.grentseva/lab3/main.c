#include <stdio.h>
#include <sys/types.h> 
#include <unistd.h>

void printID();
void fileOpen(char* filename);

int main(int argc, char* argv[]){

    if (argc != 2){
        fprintf(stderr, "%s\n", "Enter the filename");
        return 1;
    }

    uid_t real = getuid();
    uid_t effective = geteuid();

    printf("Without setuid:\n");
    printf("Real user ID: %d\n", real);
    printf("Effective user ID: %d\n", effective);

    fileOpen(argv[1]);
    if (setuid(effective) == -1){
        perror("Fail setuid");
        return 1;
    }

    printf("With setuid:\n");
    printf("Real user ID: %d\n", real);
    printf("Effective user ID: %d\n", effective);

    fileOpen(argv[1]);
    return 0;
}

void fileOpen(char* filename){
    FILE* file;
    if (!(file = fopen(filename, "r"))){
        perror("Coudn't open file");
        return;
    }
    if (fclose(file)) {
        perror("Couldn't close file");
        return;
    }
}