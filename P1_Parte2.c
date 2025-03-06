#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int valor;
    int pos1;
    int pos2;
} Resultado;

Resultado encontrarDuplicado(int n, int A[]) {
    int mitad = n / 2;
    int primera_mitad[3 * n + 1];
    int segunda_mitad[3 * n + 1];

    for (int i = 0; i <= 3 * n; i++) {
        primera_mitad[i] = -1;
        segunda_mitad[i] = -1;
    }

    for (int i = 0; i < mitad + 1; i++) {
        primera_mitad[A[i]] = i;
    }
    for (int i = mitad + 1; i < n; i++) {
        segunda_mitad[A[i]] = i;
    }

    for (int i = 0; i <= 3 * n; i++) {
        if (primera_mitad[i] != -1 && segunda_mitad[i] != -1) {
            Resultado resultado = {i, primera_mitad[i], segunda_mitad[i]};
            return resultado;
        }
    }

    Resultado resultado = {-1, -1, -1};
    return resultado;
}

void medirTiempoEjecucion(int min_n, int max_n, int paso) {
    FILE *fp = fopen("datos.txt", "w");
    if (!fp) {
        printf("Error al abrir archivo para datos.\n");
        return;
    }

    for (int n = min_n; n <= max_n; n += paso) {
        int A[n];
        srand(time(0));
        for (int i = 0; i < n; i++) {
            A[i] = rand() % (3 * n + 1);
        }

        double tiempo_total = 0;
        // Ejecutamos varias veces para mejorar precisión
        int repeticiones = 1000;  
        for (int i = 0; i < repeticiones; i++) {
            clock_t inicio = clock();
            Resultado resultado = encontrarDuplicado(n, A);
            clock_t fin = clock();
            tiempo_total += ((double)(fin - inicio)) / CLOCKS_PER_SEC;
        }

        double tiempo_promedio = tiempo_total / repeticiones;
        fprintf(fp, "%d %lf\n", n, tiempo_promedio);
    }

    fclose(fp);
}

void graficarResultados() {
    FILE *gp = popen("gnuplot -persistent", "w");
    if (!gp) {
        printf("Error al abrir Gnuplot.\n");
        return;
    }

    fprintf(gp, "set title 'Tiempo de ejecución vs. Tamaño de entrada'\n");
    fprintf(gp, "set xlabel 'Tamaño de entrada (n)'\n");
    fprintf(gp, "set ylabel 'Tiempo de ejecución (segundos)'\n");
    fprintf(gp, "plot 'datos.txt' with linespoints title 'Tiempo de ejecución'\n");

    pclose(gp);
}

int main() {
    int min_n = 10, max_n = 1000, paso = 50;

    medirTiempoEjecucion(min_n, max_n, paso);
    graficarResultados();

    return 0;
}
