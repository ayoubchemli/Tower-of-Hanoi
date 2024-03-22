#include <stdio.h>
#include <stdlib.h>


void hanoi(int n, char source, char auxiliary, char destination) {
    if (n == 1) {
        printf("Déplacer le disque 1 de %c vers %c\n", source, destination);
        return;
    }

    hanoi(n - 1, source, destination, auxiliary);
    printf("Deplacer le disque %d de %c vers %c\n", n, source, destination);
    hanoi(n - 1, auxiliary, source, destination);
}

int main() {
    int n;
    printf("Entrez le nombre de disques : ");
    scanf("%d", &n);
    hanoi(n, 'A', 'B', 'C');
    return 0;
}

//version algorithme:

/*ALGORITHME hanoi(n, source, auxiliaire, destination)
    SI n = 1 ALORS
        AFFICHER "Déplacer le disque 1 de", source, "vers", destination
    SINON
        hanoi(n - 1, source, destination, auxiliaire)
        AFFICHER "Déplacer le disque", n, "de", source, "vers", destination
        hanoi(n - 1, auxiliaire, source, destination)
    FIN SI
FIN ALGORITHME

ALGORITHME principal()
    DÉCLARER n ENTIER
    AFFICHER "Entrez le nombre de disques : "
    LIRE n
    hanoi(n, 'A', 'B', 'C')
FIN ALGORITHME*/


 //complexity calcul:

 /*Pour analyser la complexité temporelle, nous pouvons examiner le nombre de déplacements nécessaires pour différentes valeurs de `n`.

1. Lorsque `n = 1` :
   - Il faut un seul déplacement pour déplacer le seul disque de la tige source à la tige destination.

2. Lorsque `n = 2` :
   - Il faut 3 déplacements.
     - Déplacer le disque 1 de la source vers l'auxiliaire.
     - Déplacer le disque 2 de la source vers la destination.
     - Déplacer le disque 1 de l'auxiliaire vers la destination.

3. Lorsque `n = 3` :
   - Il faut 7 déplacements.
     - Déplacer les disques 1 et 2 de la source vers la destination en utilisant l'auxiliaire.
     - Déplacer le disque 3 de la source vers la destination.
     - Déplacer les disques 1 et 2 de l'auxiliaire vers la destination.

En général, pour `n` disques, le nombre de déplacements peut être exprimé comme suit :
\[ T(n) = 2T(n - 1) + 1 \]

Pour résoudre cette récurrence, nous pouvons développer la formule pour quelques valeurs de `n` :

- Lorsque `n = 1`, \( T(1) = 2^1 - 1 = 1 \) déplacement.
- Lorsque `n = 2`, \( T(2) = 2^2 - 1 = 3 \) déplacements.
- Lorsque `n = 3`, \( T(3) = 2^3 - 1 = 7 \) déplacements.
- Lorsque `n = 4`, \( T(4) = 2^4 - 1 = 15 \) déplacements.
- Lorsque `n = 5`, \( T(5) = 2^5 - 1 = 31 \) déplacements.

En général, pour `n` disques, le nombre total de déplacements est donné par :
\[ T(n) = 2^n - 1 \]

Ainsi, la complexité temporelle de l'algorithme récursif de résolution des tours de Hanoi est exponentielle, avec une complexité en temps de \( O(2^n) \). Cela signifie que le nombre de déplacements nécessaires pour résoudre le problème double à chaque ajout d'un disque. Cette complexité croît rapidement avec la taille du problème, ce qui en fait un problème NP-complet.*/
