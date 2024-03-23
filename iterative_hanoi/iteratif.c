#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

clock_t start,end;

//la déclaration de la structure pile 
typedef struct {
    int *pile;
    int sommet;
} Pile;

// les fonctions élémentaires 
void initPile(Pile *p, int n) {
    p->pile = (int*) malloc(n * sizeof(int));
    p->sommet = -1;
}

int vide(Pile *p) {
    return p->sommet == -1;
}

int sommet(Pile *p) {
    return p->pile[p->sommet];
}

void empiler(Pile *p, int x) {
    p->pile[++(p->sommet)] = x;
}

int depiler(Pile *p) {
    return p->pile[(p->sommet)--];
}

void afficherPile(Pile *p) {
    for(int i = 0; i <= p->sommet ; i++) {
        printf("%d ", p->pile[i]);
    }
    printf("\n");
}

//remplissage d'un piquet
void remplir(Pile *p, int n) {
    for(int i = n; i >= 1; i--) {
        empiler(p, i);
    }
}

void afficherPiquets(Pile *p1, Pile *p2, Pile *p3) {
    printf("A : ");
    afficherPile(p1);
    printf("B : ");
    afficherPile(p2);
    printf("C : ");
    afficherPile(p3);
}

//la resolution des tours d'hanoi 
void resolutionIteratif(Pile *p1, Pile *p2, Pile *p3, int n) {
   int indic = 0;

    // Parité de n
    if (n % 2 == 0) {
        indic = 1; // Si le nombre de disques est pair
    } else {
        indic = -1; // Si le nombre de disques est impair
    }

    // Calcul du nb de déplacement min
    int deplacementMin = (int) pow(2, n) - 1;//le nombre de déplacement qui seront effectués (2^n-1)

    printf("-------------------\n");

    for (int i = 0; i < deplacementMin; i++) {
        // n Paire
        if (indic == 1) {
            if (i % 3 == 0) {
    
                if (!vide(p1) && (vide(p2) || sommet(p1) < sommet(p2))) {
                    empiler(p2, depiler(p1));
                } else {
                    empiler(p1, depiler(p2));
                }
            } else if (i % 3 == 1) {
                
                if (!vide(p1) && (vide(p3) || sommet(p1) < sommet(p3))) {
                    empiler(p3, depiler(p1));
                } else {
                    empiler(p1, depiler(p3));
                }
            } else {
                
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
                
                if (!vide(p1) && (vide(p3) || sommet(p1) < sommet(p3))) {
                    empiler(p3, depiler(p1));
                } else {
                    empiler(p1, depiler(p3));
                }
            } else if (i % 3 == 1) {
                
                if (!vide(p1) && (vide(p2) || sommet(p1) < sommet(p2))) {
                    empiler(p2, depiler(p1));
                } else {
                    empiler(p1, depiler(p2));
                }
            } else {
                
                if (!vide(p3) && (vide(p2) || sommet(p3) < sommet(p2))) {
                    empiler(p2, depiler(p3));
                } else {
                    empiler(p3, depiler(p2));
                }
            }
        }
        printf("déplacement numéro :  %d \n", i+1); 
        afficherPiquets(p1, p2, p3);
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
    
    //l'initialisation des piles
    Pile p1, p2, p3;
    initPile(&p1, n);
    initPile(&p2, n);
    initPile(&p3, n);


    remplir(&p1, n);// remplissage du premier piquet par les n disques 
    printf("-------------------\n");
    printf("l'état des piquets avant le déplacement : \n");
    printf("-------------------\n");
    afficherPiquets(&p1,&p2,&p3);
    printf("-------------------\n");
    printf("l'état des piquets aprés le déplacement : \n");
    // le plus grand disque a comme numéro n , aprés le disque le moins grand c'est  n-1 et ainsi de suite ...
    
    //pour calculer le temp de la résolution 
    start=clock();   
    resolutionIteratif(&p1, &p2, &p3, n);
    end=clock();
    float time=(float)(end-start)/CLOCKS_PER_SEC;
    printf("\t\tLe temps d'execution est : %f\n\n",time);
    return 0;

}
