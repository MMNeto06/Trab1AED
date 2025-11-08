#include <stdio.h>

int testTrue() {
    return 1>0;
}

int testFalse(){
    return 1<0;
}

int main(void){
    printf("true = %d\n", testTrue());
    printf("false = %d\n", testFalse());
}