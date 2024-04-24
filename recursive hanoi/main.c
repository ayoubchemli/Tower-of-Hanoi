#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Definition de la structure pour la pile
typedef struct {
    int *pile;
    int sommet;
} Pile;

// Fonction pour initialiser la pile
void initPile(Pile *p, int n) {
    p->pile = (int*) malloc(n * sizeof(int));
    if (p->pile == NULL) {
        printf("Echec de l'allocation memoire\n");
        exit(EXIT_FAILURE);
    }
    p->sommet = -1;
}

// Fonction pour verifier si la pile est vide
int vide(Pile *p) {
    return p->sommet == -1;
}

// Fonction pour retourner le sommet de la pile
int sommet(Pile *p) {
    return p->pile[p->sommet];
}

// Fonction pour empiler un element sur la pile
void push(Pile *p, int x) {
    p->pile[++(p->sommet)] = x;
}

// Fonction pour depiler un element de la pile
int pop(Pile *p) {
    return p->pile[(p->sommet)--];
}

// Fonction pour afficher la pile
void afficherPile(Pile *p) {
    for (int i = 0; i <= p->sommet; i++) {
        printf("%d ", p->pile[i]);
    }
    printf("\n");
}

// Fonction pour remplir la pile avec des nombres de n a 1
void remplir(Pile *p, int n) {
    for (int i = n; i >= 1; i--) {
        push(p, i);
    }
}

// Fonction pour resoudre le probleme de la Tour de Hanoi
void hanoi(int n, char source, char auxiliary, char destination, char finalDestination, Pile *pile) {
    if (n == 1) {
        printf("Deplacer le disque 1 de %c vers %c\n", source, destination);
        if (destination == finalDestination) {
            push(pile, n);
        } else if (source == finalDestination) {
            pop(pile);
        }
        return;
    }
    hanoi(n - 1, source, destination, auxiliary, finalDestination, pile);
    printf("Deplacer le disque %d de %c vers %c\n", n, source, destination);
    if (destination == finalDestination) {
        push(pile, n);
    } else if (source == finalDestination) {
        pop(pile);
    }
    hanoi(n - 1, auxiliary, source, destination, finalDestination, pile);
}

// Fonction pour verifier la solution
bool verification(int n, Pile *pile) {
    int count = 0;
    while (!vide(pile)) {
        int a = pop(pile);
        count++;
        if (!vide(pile) && a > sommet(pile)) {
            printf("Solution invalide\n");
            return false;
        }
    }
    if (count != n) {
        printf("Solution invalide\n");
        return false;
    }
    printf("Solution valide\n");
    return true;
}

int main() {
    Pile pile;
    int n;

    printf("Entrez le nombre de disques : ");
    scanf("%d", &n);

    initPile(&pile, n);
    hanoi(n, 'A', 'B', 'C', 'C', &pile);
    verification(n, &pile);

    free(pile.pile); // Liberer la memoire allouee dynamiquement
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
