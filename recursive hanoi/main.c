#include <stdio.h>
#include <stdlib.h>


void hanoi(int n, char source, char auxiliary, char destination) {
    if (n == 1) {
        printf("D�placer le disque 1 de %c vers %c\n", source, destination);
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
        AFFICHER "D�placer le disque 1 de", source, "vers", destination
    SINON
        hanoi(n - 1, source, destination, auxiliaire)
        AFFICHER "D�placer le disque", n, "de", source, "vers", destination
        hanoi(n - 1, auxiliaire, source, destination)
    FIN SI
FIN ALGORITHME

ALGORITHME principal()
    D�CLARER n ENTIER
    AFFICHER "Entrez le nombre de disques : "
    LIRE n
    hanoi(n, 'A', 'B', 'C')
FIN ALGORITHME*/


 //complexity calcul:

 /*Pour analyser la complexit� temporelle, nous pouvons examiner le nombre de d�placements n�cessaires pour diff�rentes valeurs de `n`.

1. Lorsque `n = 1` :
   - Il faut un seul d�placement pour d�placer le seul disque de la tige source � la tige destination.

2. Lorsque `n = 2` :
   - Il faut 3 d�placements.
     - D�placer le disque 1 de la source vers l'auxiliaire.
     - D�placer le disque 2 de la source vers la destination.
     - D�placer le disque 1 de l'auxiliaire vers la destination.

3. Lorsque `n = 3` :
   - Il faut 7 d�placements.
     - D�placer les disques 1 et 2 de la source vers la destination en utilisant l'auxiliaire.
     - D�placer le disque 3 de la source vers la destination.
     - D�placer les disques 1 et 2 de l'auxiliaire vers la destination.

En g�n�ral, pour `n` disques, le nombre de d�placements peut �tre exprim� comme suit :
\[ T(n) = 2T(n - 1) + 1 \]

Pour r�soudre cette r�currence, nous pouvons d�velopper la formule pour quelques valeurs de `n` :

- Lorsque `n = 1`, \( T(1) = 2^1 - 1 = 1 \) d�placement.
- Lorsque `n = 2`, \( T(2) = 2^2 - 1 = 3 \) d�placements.
- Lorsque `n = 3`, \( T(3) = 2^3 - 1 = 7 \) d�placements.
- Lorsque `n = 4`, \( T(4) = 2^4 - 1 = 15 \) d�placements.
- Lorsque `n = 5`, \( T(5) = 2^5 - 1 = 31 \) d�placements.

En g�n�ral, pour `n` disques, le nombre total de d�placements est donn� par :
\[ T(n) = 2^n - 1 \]

Ainsi, la complexit� temporelle de l'algorithme r�cursif de r�solution des tours de Hanoi est exponentielle, avec une complexit� en temps de \( O(2^n) \). Cela signifie que le nombre de d�placements n�cessaires pour r�soudre le probl�me double � chaque ajout d'un disque. Cette complexit� cro�t rapidement avec la taille du probl�me, ce qui en fait un probl�me NP-complet.*/