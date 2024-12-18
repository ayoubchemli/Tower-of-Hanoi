#include <stdio.h>
#include <stdlib.h>
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


//la resolution des tours d'hanoi 
void resolutionIteratif(Pile *p1, Pile *p2, Pile *p3, int n,char T[]) {
   int indic = 0;
   //on  calcule pas dabs la complexité les instructions qui contiennent le T[] car il ont une relation avec le graphic et non pas la resolution
   int k = 0 ;// X
   
    // Parité de n
    if (n % 2 == 0) {
        indic = 1; // Si le nombre de disques est pair
    } else {
        indic = -1; // Si le nombre de disques est impair
    }

    // Calcul du nb de déplacement min
    int deplacementMin = (1<<n)-1;//le nombre de déplacement qui seront effectués (2^n-1)

    printf("-----------------------------------------\n");

    for (int i = 0; i < deplacementMin; i++) {
        // n Paire
        if (indic == 1) {
            if (i % 3 == 0) {
    
                if (!vide(p1) && (vide(p2) || sommet(p1) < sommet(p2))) {
                    empiler(p2, depiler(p1));
                    T[k] = 'A' ;//X
                    T[k+1] = 'B';//X
                } else {
                    empiler(p1, depiler(p2));
                    T[k] = 'B' ;//X 
                    T[k+1] = 'A';//X
                }
            } else if (i % 3 == 1) {
                
                if (!vide(p1) && (vide(p3) || sommet(p1) < sommet(p3))) {
                    empiler(p3, depiler(p1));
                    T[k] = 'A' ;//X 
                    T[k+1] = 'C';//X
                } else {
                    empiler(p1, depiler(p3));
                    T[k] = 'C' ;//X 
                    T[k+1] = 'A';//X
                }
            }else {
                
                if (!vide(p2) && (vide(p3) || sommet(p2) < sommet(p3))) {
                    empiler(p3, depiler(p2));
                    T[k] = 'B' ;//X 
                    T[k+1] = 'C';//X
                } else {
                    empiler(p2, depiler(p3));
                    T[k] = 'C' ;//X 
                    T[k+1] = 'B';//X
                }
            }
        }
        // n Impair
        else {
            if (i % 3 == 0) {
                
                if (!vide(p1) && (vide(p3) || sommet(p1) < sommet(p3))) {
                    empiler(p3, depiler(p1));
                    T[k] = 'A' ;//X 
                    T[k+1] = 'C';//X
                } else {
                    empiler(p1, depiler(p3));
                    T[k] = 'C' ;//X 
                    T[k+1] = 'A';//X
                }
            } else if (i % 3 == 1) {
                
                if (!vide(p1) && (vide(p2) || sommet(p1) < sommet(p2))) {
                    empiler(p2, depiler(p1));
                    T[k] = 'A' ;//X 
                    T[k+1] = 'B';
                } else {
                    empiler(p1, depiler(p2));
                    T[k] = 'B' ;//X 
                    T[k+1] = 'A';//X
                }
            } else {
                
                if (!vide(p3) && (vide(p2) || sommet(p3) < sommet(p2))) {
                    empiler(p2, depiler(p3));
                    T[k] = 'C' ;//X 
                    T[k+1] = 'B';//X
                } else {
                    empiler(p3, depiler(p2));
                    T[k] = 'B' ;//X 
                    T[k+1] = 'C';//X
                }
            }
        }
        k=k+2;
    }
}

int pileDecroissant(Pile *p) {
    int x = depiler(p);
    while (p->sommet != -1) {
        int next = depiler(p);
        if (next < x) {
            return -1;
        }
        x = next;
    }
    return 1;
}

// la fonction de la vérification 
int verif_iterative(Pile A,Pile B,Pile C)
{
    if (vide(&A)&&vide(&B)&&pileDecroissant(&C))
    {
        return 1 ;
    }
    else
    {
        return -1 ; 
    }

}
