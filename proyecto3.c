// Proyecto3 C
// Grupo 4
// Integrantes: Brenda Castro, Bryan Mora y Juan Diego Arce


#include <stdio.h>
#include <stdlib.h>

// Se reserva memoria dinámica y devuelve las direcciones de inicio de cada fila.
int reservarMemoria(int ***matriz, int filas, int columnas) {
    printf("Ingrese los elementos de la matriz (%dx%d):\n", filas, columnas);

    // Reserva la memoria para la matriz.
    *matriz = (int **)malloc(filas * sizeof(int *));
    if (*matriz == NULL) {
        printf("Error al reservar memoria para las filas.\n");
        return -1;
    }
    for (int i = 0; i < filas; i++) {
        (*matriz)[i] = (int *)malloc(columnas * sizeof(int));
        if ((*matriz)[i] == NULL) {
            printf("Error al reservar memoria para las columnas de la fila %d.\n", i);
            return -1;
        }
    }
    // Inicializa la matriz con ceros.
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            (*matriz)[i][j] = 0;
        }
    }
    // Lee las posiciones de los números e imprime las direcciones de inicio de cada fila.
    printf("Ingrese las posiciones de los números (fila, columna) o -1 para terminar:\n");
    printf("Debe ingresar primero la columna, presionar enter y luego la fila\n");
    int fila, columna;
    while (1) {
        // Revisa que el número de entrada para la fila sea un entero.
        if (scanf("%d", &fila) != 1) {
            printf("Error: Se esperaba un número entero. Inténtelo de nuevo.\n");
            fflush(stdin);
            continue;
        }
        // Verifica si el usuario ingresa -1.
        if (fila == -1) {
            break;
        }
        // Revisa que el número de entrada para la columna sea un entero.
        if (scanf("%d", &columna) != 1) {
            printf("Error: Debe ingresar un número entero, inténtelo de nuevo.\n");
            fflush(stdin);
            continue;
        }
        // Verifica los límites de la matriz.
        if (fila < 0 || fila >= filas || columna < 0 || columna >= columnas) {
            printf("Posición fuera de los límites de la matriz, inténtelo de nuevo.\n");
            continue;
        }
        // Imprime la dirección de inicio de la fila.
        if (columna == 0) {
            printf("Dirección de inicio de la fila %d: %p\n", fila, (void *)&(*matriz)[fila][0]);
        }
        // Almacena el número en la matriz.
        printf("Ingrese el valor para la posición (%d, %d): ", fila, columna);
        if (scanf("%d", &(*matriz)[fila][columna]) != 1) {
            printf("Error: Debe ingresar un número entero, nténtelo de nuevo.\n");
            fflush(stdin);
            continue;
        }
    }
    return 0;
}
int main() {
    int filas, columnas;

    printf("Ingrese el número de filas de la matriz: ");
    scanf("%d", &filas);

    printf("Ingrese el número de columnas de la matriz: ");
    scanf("%d", &columnas);

    int **matriz;
    int resultado = reservarMemoria(&matriz, filas, columnas);

    // Libera la memoria.
    for (int i = 0; i < filas; i++) {
        free(matriz[i]);
    }
    free(matriz);
    return resultado;
}
