# Fork, Pipe & Array
```
g++ main.cpp
./a.out
```

Programa que de manera binarizada envia un arreglo desde un proceso a otro (desde el padre al hijo).

El proceso hijo lo modifica, y lo envia de vuelta al proceso padre.

En vez de enviar strings, es mejor enviarlo binarizado, para que no sea necesario cortar, eliminar saltos de linea, o usar atoi.

Creado para implementar el modulo de lectura y escritura por pipe del lab 1 de sistemas operativos.

Por Felipe Vilches C.
