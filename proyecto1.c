// Proyecto C. Ejercicio 1
// Grupo 4
// Integrantes: Brenda Castro, Bryan Mora y Juan Diego Arce

/*
Programa que calcula la distancia mas corta entre ciudades, el usuario
ingresa la cantidad de ciudades y las distancias entre ellas, despues un
punto de salida y uno de destino, finalmente imprime el camino mas corto y
la distancia correspondiente
*/

// Importacion de bibliotecas necesarias
#include <stdio.h>
#include <limits.h>
#include <ctype.h>  // Necesario para la función toupper


// Funcion para encontrar el camino mas corto mediante ciclos anidados
void encontrar_camino_mas_corto(int num_ciudades, int distancias[num_ciudades][num_ciudades], int inicio, int destino) {
    int distancias_minimas[num_ciudades];
    int visitados[num_ciudades];
    int camino[num_ciudades];

    // Inicializar distancias mínimas y visitados
    for (int i = 0; i < num_ciudades; i++) {
        distancias_minimas[i] = INT_MAX; // Representacion de infinito
        visitados[i] = 0;
	camino[i] = -1;
    }

    // La distancia a la ciudad de inicio es 0
    distancias_minimas[inicio] = 0;

    // Encontrar el camino más corto
    for (int contador = 0; contador < num_ciudades - 1; contador++) {
        // Encontrar la ciudad no visitada con la distancia mínima
        int ciudad_actual = -1;
        for (int i = 0; i < num_ciudades; i++) {
            if (!visitados[i] && (ciudad_actual == -1 || distancias_minimas[i] < distancias_minimas[ciudad_actual])) {
                ciudad_actual = i;
            }
        }

        // Marcar la ciudad actual como visitada
        visitados[ciudad_actual] = 1;

        // Actualizar las distancias mínimas
        for (int vecino = 0; vecino < num_ciudades; vecino++) {
            // Verificar si hay un camino válido (distinto de -1)
            if (!visitados[vecino] && distancias[ciudad_actual][vecino] != -1) {
                int nueva_distancia = distancias_minimas[ciudad_actual] + distancias[ciudad_actual][vecino];
                if (nueva_distancia < distancias_minimas[vecino]) {
                    distancias_minimas[vecino] = nueva_distancia;
                    camino[vecino] = ciudad_actual;
                }
            }
        }
    }

    // Imprimir la distancia mínima hasta la ciudad destino
    if (distancias_minimas[destino] == INT_MAX) {
        printf("No hay un camino válido desde la ciudad %c hasta la ciudad %c.\n", 'A' + inicio, 'A' + destino);
    } else {
        printf("La distancia mínima desde la ciudad %c hasta la ciudad %c es: %d\n", 'A' + inicio, 'A' + destino, distancias_minimas[destino]);
        // Imprimir el camino
        int ciudad_actual = destino;
        int ciudades[100]; // Supongamos un tamaño máximo de 100 ciudades
        int contador_ciudades = 0;

	// La ciudad destino es un -1 en el arreglo camino
	// Se crea el vector ciudades
        while (ciudad_actual != -1) {
            ciudades[contador_ciudades] = ciudad_actual;
            contador_ciudades++;

            ciudad_actual = camino[ciudad_actual];
        }

        // Imprimir el camino en orden inverso
	// Recorre el arreglo ciudades inversamente y lo va imprimiento
	// como la retra correspondiente
	printf("Camino ");
        for (int i = contador_ciudades - 1; i >= 0; i--) {
            printf("%c", 'A' + ciudades[i]);
            if (i > 0) {
                printf(" -> ");
            }
        }

        printf("\n");
    }
}

// Funcion principal
// Recibe la informacion del usuario
int main() {
    int num_ciudades;

    // Preguntar la cantidad de ciudades
    printf("Ingrese la cantidad de ciudades: ");
    scanf("%d", &num_ciudades);

    // Verifica que el número de ciudades sea válido segun el numero de  letras del abecedario
    if (num_ciudades < 1 || num_ciudades > 26) {
        printf("Número de ciudades no válido. Debe estar entre 1 y 26.\n");
        return 1;  // Termina el programa con un código de error
    }

    // Crear una matriz para representar las distancias entre ciudades
    int distancias[num_ciudades][num_ciudades];

    // Inicializar la matriz con -1 para indicar ciudades no conectadas
    for (int i = 0; i < num_ciudades; i++) {
        for (int j = 0; j < num_ciudades; j++) {
            distancias[i][j] = -1;
        }
    }

    // Ingresar las distancias entre ciudades
    for (int i = 0; i < num_ciudades; i++) {
        for (int j = i + 1; j < num_ciudades; j++) {
            int distancia;
            printf("Ingrese la distancia entre la ciudad %c y la ciudad %c (-1 si estan desconectadas): ", 'A' + i, 'A' + j);
            scanf("%d", &distancia);

            // Asignar la distancia a ambas direcciones
            distancias[i][j] = distancia;
            distancias[j][i] = distancia;
        }
    }

    // Preguntar ciudad de inicio y destino
    char ciudad_inicio, ciudad_destino;
    printf("Ingrese la ciudad de inicio (A, B, C, D, E, F...): ");
    scanf(" %c", &ciudad_inicio);
    // Convertir la letra a mayúsculas
    ciudad_inicio = toupper(ciudad_inicio);

   // Verifica que la ciudad de inicio sea válida
    if (ciudad_inicio < 'A' || ciudad_inicio >= 'A' + num_ciudades) {
        printf("Ciudad de inicio no válida.\n");
        return 1;  // Termina el programa con un código de error
    }

    printf("Ingrese la ciudad destino (A, B, C, D, E, F...): ");
    scanf(" %c", &ciudad_destino);
    // Convertir la letra a mayúsculas
    ciudad_destino = toupper(ciudad_destino);

    // Verifica que la ciudad de destino sea válida
    if (ciudad_destino < 'A' || ciudad_destino >= 'A' + num_ciudades) {
        printf("Ciudad destino no válida.\n");
        return 1;  // Termina el programa con un código de error
    }

    // Convertir las letras a índices (A=0, B=1, ..., F=5)
    int indice_inicio = ciudad_inicio - 'A';
    int indice_destino = ciudad_destino - 'A';

    // Llamar a la función para encontrar el camino más corto
    encontrar_camino_mas_corto(num_ciudades, distancias, indice_inicio, indice_destino);

    return 0;
}

