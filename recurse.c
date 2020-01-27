#include <stdio.h>
#include <stdlib.h>
int recurse(int n);
int main(int argv, char* argc[]){
    int a = atoi(argc[1]);
    printf("%d", recurse(a));
    return EXIT_SUCCESS;
}
int recurse(int n){
    if(n == 1){
        return 2;
    }
    if(n == 0){
        return 1;
    }
    return 3*recurse(n-1) + 4*recurse(n-2)+2;
}