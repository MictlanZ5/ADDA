#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Estructura para representar un vector
typedef struct {
    double x, y;
    int clase;
} Vector;

// Función para generar un vector aleatorio
Vector generarVectorAleatorio(int clase) {
    Vector v;
    v.x = (double)rand() / RAND_MAX * 10;
    v.y = (double)rand() / RAND_MAX * 10;
    v.clase = clase;
    return v;
}

// Función para calcular la distancia entre dos vectores
double distancia(Vector v1, Vector v2) {
    return sqrt(pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2));
}

// Función para clasificar un vector utilizando k-NN
int clasificarVector(Vector v, Vector *vectores, int n, int k) {
    double distancias[n];
    for (int i = 0; i < n; i++) {
        distancias[i] = distancia(v, vectores[i]);
    }

    // Ordenar las distancias
    for (int i = 0; i < k; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (distancias[j] < distancias[minIndex]) {
                minIndex = j;
            }
        }
        double temp = distancias[i];
        distancias[i] = distancias[minIndex];
        distancias[minIndex] = temp;
    }

    // Clasificar el vector
    int clase = 0;
    for (int i = 0; i < k; i++) {
        if (vectores[i].clase == 1) {
            clase++;
        }
    }
    return clase > k / 2 ? 1 : 0;
}

int main() {
    srand(time(NULL));

    // Generar 50 vectores aleatorios de cada clase
    Vector vectores[100];
    for (int i = 0; i < 50; i++) {
        vectores[i] = generarVectorAleatorio(0);
    }
    for (int i = 50; i < 100; i++) {
        vectores[i] = generarVectorAleatorio(1);
    }

    // Clasificar un vector aleatorio
    Vector v = generarVectorAleatorio(-1);
    int clase = clasificarVector(v, vectores, 100, 5);
    printf("El vector (%f, %f) pertenece a la clase %d\n", v.x, v.y, clase);

    // Generar gráfica
    FILE *gp = popen("gnuplot -persistent", "w");
    fprintf(gp, "set title 'Clasificación de vectores'\n");
    fprintf(gp, "set xlabel 'X'\n");
    fprintf(gp, "set ylabel 'Y'\n");
    fprintf(gp, "plot '-' with points\n");
    for (int i = 0; i < 100; i++) {
        fprintf(gp, "%f %f %d\n", vectores[i].x, vectores[i].y, vectores[i].clase);
    }
    fprintf(gp, "e\n");
    pclose(gp);

    return 0;
}

