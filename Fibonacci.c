#include <stdio.h>
#include <time.h>

int fibonacci(int n){
    if(n <= 1)
        return n;
    return fibonacci(n - 1) + fibonacci (n - 2);
}

void graficarResultado(){
    FILE *gp = popen("gnuplot -persistant", "w");
    if(!gp){
        prontf("Error al abrir Gnuplot \n");
        return;
    }

    fprintf(gp, "set tittle 'Tiempo de ejecucion vs Tamanio de Entrada' \n");
    fprintf(gp, "set xlabel 'Tamanio de entrada (n)' \n");
    fprintf(gp, "set ylabel 'Tiempo de ejecucion (segundos)' \n");
    fprintf(gp, "plot 'datos.txt' with linespoints title 'Tiempo de ejecucion' \n");
}

int main(){
    int n; 
    printf("Ingrese el numero de terminos para Fibonacci: ");
    scanf("%d", &n);

    //Guardamos los datos en el archivo .txt (DatosFibo.txt)
    FILE *archivo = fopen("DatosFibo.txt", "w");
    if(!archivo){
        printf("Error al abrir el archivo de datos \n");
        return 1;
    }

    printf("La serie Fibonacci es: ");
    //Medimo el tiempo de ejecucion de cada calculo
    clock_t inicio = clock();
    int resultado = fibonacci(i);
    clock_t fin = clock();

    double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;

    printf("");

    for(int i = 0; i <= n; i++){
        printf("%d ", fibonacci(i));
    }
    return 0;
}