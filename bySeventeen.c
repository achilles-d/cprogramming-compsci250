#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int n = atoi(argv[1]);
    int i = 1;
    int multiple = 0;
    for(i = 1; i <= n; i++){
        multiple *= i * 17; 
        printf("%d \n", multiple);
    }
    return EXIT_SUCCESS;   
}