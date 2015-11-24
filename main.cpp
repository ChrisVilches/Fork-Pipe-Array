#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define LECTURA 0
#define ESCRITURA 1

using namespace std;

int main(int argc, char* argv[]){

    // Pipes
    int padreAhijo[2];
    int hijoApadre[2];
    pipe(padreAhijo);
    pipe(hijoApadre);

    // Fork
    pid_t pid;
    pid = fork();

    if(pid == 0){
        // Hijo
    
        int tamanoArreglo;
        int* arreglo;
        int i;
        
        close(padreAhijo[ESCRITURA]);   // No se necesita
        close(hijoApadre[LECTURA]);     // No se necesita

        // Leer la dimension
        read(padreAhijo[LECTURA], &tamanoArreglo, sizeof(int)); // Se lee un int

        // Malloc arreglo
        arreglo = (int*) malloc(sizeof(int) * tamanoArreglo);

        // Comenzar a leer los datos del arreglo
        for(i=0; i<tamanoArreglo; i++){
            // Lo guardo inmediatamente en el arreglo (cada read lee un int del pipe)
            // (Aunque se puede guardar en un int temporal)
            read(padreAhijo[LECTURA], &arreglo[i], sizeof(int));
        }

        close(padreAhijo[LECTURA]);     // Ya no se necesita

        // Modificamos el arreglo (podria haberse hecho en el mismo for de la lectura)
        for(i=0; i<tamanoArreglo; i++){
            arreglo[i] += i*2 + 1;      // Modificacion arbitraria
        }

        // Escribir el arreglo modificado por el pipe hacia el padre
        for(i=0; i<tamanoArreglo; i++){
            // cada write escribe un int hacia el pipe
            write(hijoApadre[ESCRITURA], &arreglo[i], sizeof(int));
        }

        close(hijoApadre[ESCRITURA]);   // Ya no se necesita

        exit(0);

    }

    // Padre

    int tamanoArreglo = 10;                     // Tamano del arreglo
    int arreglo[] = {4,5,7,7,4,5,7,8,9,0};      // Crear el arreglo
    int i;

    close(padreAhijo[LECTURA]);                 // No se necesitan
    close(hijoApadre[ESCRITURA]);

    // Primero escribimos la dimension del arreglo
    write(padreAhijo[ESCRITURA], &tamanoArreglo, sizeof(int));

    // Escribir los int al pipe
    for(i=0; i<tamanoArreglo; i++){
        write(padreAhijo[ESCRITURA], &arreglo[i], sizeof(int));
    }

    close(padreAhijo[ESCRITURA]);               // Ya termino de escribir, no se usara

    // Leer los datos que el hijo modifico
    for(i=0; i<tamanoArreglo; i++){
        // Los guardo en el arreglo original, reemplazando los valores
        read(hijoApadre[LECTURA], &arreglo[i], sizeof(int));
    }

    close(hijoApadre[LECTURA]);                 // Ya termino de leer, hay que cerrarlo

    // Imprimir
    for(i=0; i<tamanoArreglo; i++){
        cout << "Arreglo[" << i << "] = " << arreglo[i] << endl;
    }

    return 0;
}
