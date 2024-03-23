#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int *pile;
    int sommet;
} PileEntiers;

void initPile(PileEntiers *p, int n) {
    p->pile = (int*) malloc(n * sizeof(int));
    p->sommet = -1;
}

int vide(PileEntiers *p) {
    return p->sommet == -1;
}

int sommet(PileEntiers *p) {
    return p->pile[p->sommet];
}

void empiler(PileEntiers *p, int x) {
    p->pile[++(p->sommet)] = x;
}

int depiler(PileEntiers *p) {
    return p->pile[(p->sommet)--];
}

void afficherPile(PileEntiers *p) {
    for(int i = 0; i <= p->sommet ; i++) {
        printf("%d ", p->pile[i]);
    }
    printf("\n");
}


void remplir(PileEntiers *p, int n) {
    for(int i = n; i >= 1; i--) {
        empiler(p, i);
    }
}

void afficherHanoi(PileEntiers *p1, PileEntiers *p2, PileEntiers *p3) {
    printf("P1 : ");
    afficherPile(p1);
    printf("P2 : ");
    afficherPile(p2);
    printf("P3 : ");
    afficherPile(p3);
}

void resolutionIteratif(PileEntiers *p1, PileEntiers *p2, PileEntiers *p3, int n) {
   int indic = 0;

    // Parité de n
    if (n % 2 == 0) {
        indic = 1; // Si le nombre de disques est pair
    } else {
        indic = -1; // Si le nombre de disques est impair
    }

    // Calcul du nb de déplacement min
    int deplacementMin = (int) pow(2, n) - 1;

    printf("-------------------\n");

    for (int i = 0; i < deplacementMin; i++) {
        // n Paire
        if (indic == 1) {
            if (i % 3 == 0) {
                // Entre P1 et P2 (vers la droite)
                if (!vide(p1) && (vide(p2) || sommet(p1) < sommet(p2))) {
                    empiler(p2, depiler(p1));
                } else {
                    empiler(p1, depiler(p2));
                }
            } else if (i % 3 == 1) {
                // Entre P1 et P3 (vers la droite)
                if (!vide(p1) && (vide(p3) || sommet(p1) < sommet(p3))) {
                    empiler(p3, depiler(p1));
                } else {
                    empiler(p1, depiler(p3));
                }
            } else {
                // Entre P2 et P3
                if (!vide(p2) && (vide(p3) || sommet(p2) < sommet(p3))) {
                    empiler(p3, depiler(p2));
                } else {
                    empiler(p2, depiler(p3));
                }
            }
        }
        // n Impair
        else {
            if (i % 3 == 0) {
                // Entre P1 et P3
                if (!vide(p1) && (vide(p3) || sommet(p1) < sommet(p3))) {
                    empiler(p3, depiler(p1));
                } else {
                    empiler(p1, depiler(p3));
                }
            } else if (i % 3 == 1) {
                // Entre P1 et P2 (vers la gauche)
                if (!vide(p1) && (vide(p2) || sommet(p1) < sommet(p2))) {
                    empiler(p2, depiler(p1));
                } else {
                    empiler(p1, depiler(p2));
                }
            } else {
                // Entre P2 et P3
                if (!vide(p3) && (vide(p2) || sommet(p3) < sommet(p2))) {
                    empiler(p2, depiler(p3));
                } else {
                    empiler(p3, depiler(p2));
                }
            }
        }
        printf("déplacement numéro :  %d \n", i+1); 
        afficherHanoi(p1, p2, p3);
        printf("-------------------\n");
    }
}

int main() {
    int n;
    
    do
    {
    printf("Saisir le nombre de disques : ");
    scanf("%d", &n);   
    } while (n<=0);
    

    PileEntiers p1, p2, p3;
    initPile(&p1, n);
    initPile(&p2, n);
    initPile(&p3, n);


    remplir(&p1, n);// on fait remplir le premier piquer par les disques 
    printf("-------------------\n");
    printf("l'état des piquets avant le déplacement : \n");
     printf("-------------------\n");
    afficherHanoi(&p1,&p2,&p3);
    printf("-------------------\n");
    printf("l'état des piquets aprés le déplacement : \n");
    resolutionIteratif(&p1, &p2, &p3, n);
    

    // le plus grand disque a comme numéro 1 , aprés le disque le moins grand c'est  2 et ainsi de suite ...
    return 0;

}
