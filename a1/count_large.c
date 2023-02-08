#include <stdio.h>
#include <stdlib.h>


// TODO: Implement a helper named check_permissions that matches the prototype below.
int check_permissions(char *, char *);


int main(int argc, char** argv) {
    if (!(argc == 2 || argc == 3)) {
        fprintf(stderr, "USAGE: count_large size [permissions]\n");
        return 1;
    }
    
    // TODO: Process command line arguments.
    int request_num = atoi(argv[1]);
    int sum = 0;
    // TODO: Call check_permissions as part of your solution to count the files to
    // compute and print the correct value.
    char permission[50], str1[50], str2[50],  str3[50], str4[50], str5[50], str6[50], str7[50];
    char ignore[50];
    int size;
    scanf("%[^\n]%*c", ignore);

    while (scanf("%s%s%s%s%d%s%s%s%s", permission, str1, str2, str3, &size, str4, str5, str6, str7)!= EOF){
        char *need_to_check = permission + 1;
        if (size >= request_num){
            if (argc == 3){
                if(check_permissions(need_to_check, argv[2]) ==0){
                    sum += 1;
                }
            }else{
                sum += 1;
            }
        }
    }
    printf("%d\n", sum);
    return 0;
}

int check_permissions(char *arry1, char *arry2){

    for(int i = 0; i <9; i++){
        char need_to_check = arry1[i];
        char correct = arry2[i];
        if (correct == '-'){
            continue;
        } 
        if (!(need_to_check == correct)){
            return 1;
        }
    }
    return 0;
}