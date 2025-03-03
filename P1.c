#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int valor;
    int pos1;
    int pos2;
} Resultado;

Resultado encontrarDuplicado(int n) {
    // Inicializar el generador de números aleatorios
    srand(time(0));

    // Crear el arreglo con valores aleatorios entre 0 y 3n
    int A[n];
    for (int i = 0; i < n; i++) {
        A[i] = rand() % (3 * n + 1);
    }

    // Mostrar el arreglo generado (opcional para depuración)
    printf("Arreglo generado: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");

    // Crear arreglos para almacenar las posiciones de los valores en cada mitad
    int mitad = n / 2;
    int primera_mitad[3 * n + 1];
    int segunda_mitad[3 * n + 1];

    // Inicializar los arreglos con -1
    for (int i = 0; i <= 3 * n; i++) {
        primera_mitad[i] = -1;
        segunda_mitad[i] = -1;
    }

    // Guardamos los valores y posiciones en cada mitad
    for (int i = 0; i < mitad +1; i++) {
        primera_mitad[A[i]] = i;
    }
    for (int i = mitad + 1; i < n; i++) {
        segunda_mitad[A[i]] = i;
    }

    // Buscar el primer valor que se repite en ambas mitades
    for (int i = 0; i <= 3 * n; i++) {
        if (primera_mitad[i] != -1 && segunda_mitad[i] != -1) {
            Resultado resultado = {i, primera_mitad[i], segunda_mitad[i]};
            return resultado;
        }
    }

    // Si no se encuentra ningún duplicado, devolver valores inválidos
    Resultado resultado = {-1, -1, -1};
    return resultado;
}

int main() {
    int n = 10; // Tamaño del arreglo
    Resultado resultado = encontrarDuplicado(n);

    if (resultado.valor != -1) {
        printf("Valor encontrado: %d, Posiciones: %d y %d\n", resultado.valor, resultado.pos1, resultado.pos2);
    } else {
        printf("No se encontraron valores repetidos en ambas mitades.\n");
    }

    return 0;
}