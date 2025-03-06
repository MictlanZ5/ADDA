/*
Escuela Superior de Computo (ESCOM IPN)
Grupo: 
3CM3
Autores:
Segundo Cantero Jonathan Axel 
Zuñiga Lara José Alberto

#include <stdio.h>
#include <time.h>

// Función para calcular el MCD con el algoritmo de Euclides y contar iteraciones
int euclides(int m, int n, int *contador) {
    while (n != 0) {
        (*contador)++;  // Contador de iteraciones
        int r = m % n;
        m = n;
        n = r;
    }
    return m;
}

// Función para generar el n-ésimo número de Fibonacci
int fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
    int m, n, contador = 0;
    clock_t inicio, fin;
    double tiempo_ejecucion;

    // Casos generales
    m = 48, n = 18; // Ejemplo con valores comunes
    contador = 0;
    inicio = clock();
    int mcd = euclides(m, n, &contador);
    fin = clock();
    tiempo_ejecucion = (double)(fin - inicio) / CLOCKS_PER_SEC;
    printf("MCD(%d, %d) = %d, Iteraciones: %d, Tiempo: %f segundos\n", m, n, mcd, contador, tiempo_ejecucion);

    // Peor caso: números consecutivos de Fibonacci
    int fib1 = fibonacci(30); // Un Fibonacci grande
    int fib2 = fibonacci(29); // Fibonacci anterior (peor caso)
    contador = 0;
    inicio = clock();
    mcd = euclides(fib1, fib2, &contador);
    fin = clock();
    tiempo_ejecucion = (double)(fin - inicio) / CLOCKS_PER_SEC;
    printf("MCD(%d, %d) = %d, Iteraciones: %d, Tiempo: %f segundos (Peor caso con Fibonacci)\n", fib1, fib2, mcd, contador, tiempo_ejecucion);

    return 0;
}
