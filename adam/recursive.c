#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "resolution.c"





int k = 0;
// Fonction pour resoudre le probleme de la Tour de Hanoi
void resolutionRecursive(int n, char source, char auxiliary, char destination, char T[]) {
    if (n == 1) {
        // printf("Deplacer le disque 1 de %c vers %c\n", source, destination);
        T[k] = source;
        T[k+1] = destination;
        k += 2;
        
        return;
    }
    resolutionRecursive(n - 1, source, destination, auxiliary, T);
    // printf("Deplacer le disque %d de %c vers %c\n", n, source, destination);
    T[k] = source;
    T[k+1] = destination;
    k += 2;
    
    resolutionRecursive(n - 1, auxiliary, source, destination, T);
}




