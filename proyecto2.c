// Proyecto 2
// Grupo 4
// Integrantes: Brenda Castro, Bryan Mora y Juan Diego Arce

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#define Pi 3.141592

// Fincion que encuentra el angulo entre dos vectores, teniendo 3 puntos
float calcularAngulo(float A[], float B[], float C[]) {
    float vector1x = A[0] - B[0];
    float vector1y = A[1] - B[1];
    float vector2x = C[0] - B[0];
    float vector2y = C[1] - B[1];

    float productoPunto = vector1x * vector2x + vector1y * vector2y;
    float magnitud1 = sqrt(vector1x * vector1x + vector1y * vector1y);
    float magnitud2 = sqrt(vector2x * vector2x + vector2y * vector2y);

    // Calcular el angulo, en radianes, usando la formula del producto punto
    float anguloRadianes = acos(productoPunto / (magnitud1 * magnitud2));
    return anguloRadianes;
}

// Funcion de comparacion para qsort
int compararCoordenadas(const void *a, const void *b) {
    const float *coordA = *(const float **)a;
    const float *coordB = *(const float **)b;

    // Calcula angulos
    float anguloA = atan2(coordA[1], coordA[0]);
    float anguloB = atan2(coordB[1], coordB[0]);

    // Compara angulos
    if (anguloA < anguloB) return -1;
    if (anguloA > anguloB) return 1;
    return 0;
}

// Funcion que determina si el determinante de dos vectores es negativo o positivo
int esConvexo(float A[], float B[], float C[]){
    float vector1x = A[0] - B[0];
    float vector1y = A[1] - B[1];
    float vector2x = C[0] - B[0];
    float vector2y = C[1] - B[1];

    float det = (vector1x * vector2y)- (vector2x * vector1y);

    // Si el determinante es positivo, entonces no es convexo
    if (det < 0) return 1;
    else if (det > 0) return 0;
}

int main() {
    int maxPuntos;
    printf("Ingrese las coordenadas en forma de 'x y', debe ingresar por lo menos 3 coordenadas\n");
    printf("Ingrese el numero total de coordenadas: ");
    scanf("%d", &maxPuntos);

    if (maxPuntos < 3){
        printf("Se ingreso menos de 3 puntos\n");
        return 1;
    }

    // Guarda el espacio en memoria
    float angulos[maxPuntos];
    float **coordenadas = (float **)malloc(maxPuntos * sizeof(float *));
    for (int i = 0; i < maxPuntos; i++) {
        coordenadas[i] = (float *)malloc(2 * sizeof(float));
    }

    // Ingresar coordenadas
    for (int i = 0; i < maxPuntos; i++) {
        printf("Ingrese coordenada %d 'x y' (x espacio y): ", i + 1);
        scanf("%f %f", &coordenadas[i][0], &coordenadas[i][1]);
    }

    // Ordenar las coordenadas en sentido contrario a las manecillas del reloj
    // Esto ayuda a determinar si es convexo o no
    qsort(coordenadas, maxPuntos, sizeof(float *), compararCoordenadas);

    // Con los puntos ordenados, se determina si es convexo el poligono
    int resultado;
    for (int c = 0; c < maxPuntos; c++){
        if (c < maxPuntos -2){
            resultado = esConvexo(coordenadas[c], coordenadas[c + 1], coordenadas[c + 2]);
        }
        else if (c == maxPuntos - 2){
            resultado = esConvexo(coordenadas[c], coordenadas[c + 1], coordenadas[0]);
        }
        else if (c == maxPuntos - 1){
            resultado = esConvexo(coordenadas[c], coordenadas[0], coordenadas[1]);
        }

        if (resultado == 0){
            printf("El poligono es concavo, por lo que es invalido\n");
            goto memLib;
        }
    }
    
    // Es convexo, entonces se calculan los angulos internos
    for (int k = 0; k < maxPuntos; k++){
        if (k < maxPuntos -2){
            angulos[k] = calcularAngulo(coordenadas[k], coordenadas[k + 1], coordenadas[k + 2]);
        }
        else if (k == maxPuntos - 2){
            angulos[k] = calcularAngulo(coordenadas[k], coordenadas[k + 1], coordenadas[0]);
        }
        else if (k == maxPuntos - 1){
            angulos[k] = calcularAngulo(coordenadas[k], coordenadas[0], coordenadas[1]);
        }
    }

    // Se muestran los angulos calculados
    for (int a = 0; a < maxPuntos; a++) {
        printf("Angulo %d en radianes: %f\n", a + 1, angulos[a]);
    }

    // Liberar memoria
    memLib:
    for (int i = 0; i < maxPuntos; i++) {
        free(coordenadas[i]);
    }
    free(coordenadas);

    return 0;
}
