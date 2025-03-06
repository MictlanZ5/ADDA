#include <stdio.h>

int fibonacci(int n){
    if(n <= 1)
        return n;
    return fibonacci(n - 1) + fibonacci (n - 2);
}

int main(){
    int n; 
    printf("Ingrese el numero de terminos para Fibonacci: ");
    scanf("%d", &n);

    printf("La serie Fibonacci es: ");
    for(int i = 0; i <= n; i++){
        printf("%d ", fibonacci(i));
    }
    return 0;
}