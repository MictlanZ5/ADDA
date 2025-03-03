#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int valor;
    int pos1;
    int pos2;
} Resultado;


Resultado encontrarDuplicado(int n, int A[]) {
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
    for (int i = 0; i < mitad + 1; i++) {
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

void graficar(int n, int A[], Resultado resultado){
    FILE *gp = popen("gnuplot -persistent", "w");
    fprintf(gp, "set title 'Valores generados y duplicado encontrado'\n");
    fprintf(gp, "set xlabel 'Índice'\n");
    fprintf(gp, "set ylabel 'Valor'\n");
    fprintf(gp, "plot '-' with points pointtype 7 title 'Valores', '-' with points pointtype 5 lc rgb 'red' title 'Duplicado'\n");
    
    for (int i = 0; i < n; i++) {
        fprintf(gp, "%d %d\n", i, A[i]);
    }
    fprintf(gp, "e\n");
    
    if (resultado.valor != -1) {
        fprintf(gp, "%d %d\n", resultado.pos1, resultado.valor);
        fprintf(gp, "%d %d\n", resultado.pos2, resultado.valor);
    }
    fprintf(gp, "e\n");
    
    pclose(gp); 
}

int main() {
     // Tamaño del arreglo
    int n = 10;
    srand(time(0));
    int A[n];
    for(int i = 0; i <n; i++){
        A[i] = rand() % (3 * n + 1);
    }

    Resultado resultado = encontrarDuplicado(n, A);
    graficar(n, A, resultado);

    if (resultado.valor != -1) {
        printf("Valor encontrado: %d, Posiciones: %d y %d\n", resultado.valor, resultado.pos1, resultado.pos2);
    } else {
        printf("No se encontraron valores repetidos en ambas mitades.\n");
    }

    return 0;
} 