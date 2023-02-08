#include <stdio.h>
#include <stdlib.h>

int populate_array(int, int *);
int check_sin(int *);

int main(int argc, char **argv) {
    // TODO: Verify that command line arguments are valid.
    if (!(argc == 2)) {
        return 2;
    }
    // TODO: Parse arguments and then call the two helpers in sin_helpers.c
    // to verify the SIN given as a command line argument.
    int *array =malloc(sizeof(int)*9);
    int sin_num = atoi(argv[1]);
    populate_array(sin_num, array);
    int status = check_sin(array);
    if (status == 1){
        printf("Invalid SIN\n");
        return 1;
    }
    printf("Valid SIN\n");
    return 0;
}
