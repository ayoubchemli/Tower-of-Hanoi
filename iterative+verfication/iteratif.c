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
    
    p->pile[++(p->sommet)] = x;// 2opé
}

int depiler(Pile *p) {
   
    return p->pile[(p->sommet)--]; // 2opé
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
/*****Implementation de l'algorithme de la résolution***********/

//la resolution des tours d'hanoi 
void resolutionIteratif(Pile *p1, Pile *p2, Pile *p3, int n) {
   int indic = 0;
  
    // Parité de n
    if (n % 2 == 0) {
        indic = 1; // Si le nombre de disques est pair
    } else {
        indic = -1; // Si le nombre de disques est impair
    }


    int deplacementMin = (1<<n)-1;//le nombre de déplacements qui seront effectués (2^n-1)

  //  printf("-----------------------------------------\n");

    for (int i = 0; i < deplacementMin; i++) {
        // n Paire
        if (indic == 1) {
            if (i % 3 == 0) {
                //B1
                if (!vide(p1) && (vide(p2) || sommet(p1) < sommet(p2))) {
                    empiler(p2, depiler(p1));
                } else {
                    empiler(p1, depiler(p2));
                }
            }
            else //B2
            //B2'
            if (i % 3 == 1) {
                if (!vide(p1) && (vide(p3) || sommet(p1) < sommet(p3))) {
                    empiler(p3, depiler(p1));
                } else {
                    empiler(p1, depiler(p3));
                }
            }
            else /*B2''*/ {
                  
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
            } else
             if (i % 3 == 1) {
                
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
        {
     printf("déplacement numéro :  %d \n", i+1); // dans le calucl de la complexité on calcule pas les instructions d'affichage
      afficherPiquets(p1, p2, p3);
     printf("-------------------\n");
        }
    }
}
                  





/*Calcul de la complexité théorique de la fonction résolution itératif*/
/*
 int indic = 0 ;  -> 1 op (affectation)
 -------------------------------------------
  if (n % 2 == 0) -> 2 op ( opération du mod + comparaison du résultat avec le 0)
   {
        indic = 1;  -> 1 op (affectation)
    } else {
        indic = -1; 
    } 
    les deux blocs sont équivalents dans le nombre d'instructions , donc on choisit l'un des deux
    => 3 op dans le total
---------------------------------------------
 int deplacementMin = (1<<n)-1; -> n+2 op (1<<n ( n opération de décalage de bits + l'inititalisation à 1 ) + 1<<n -1 (soustraction)) 
 --------------------------------------------
 le calcul du complexité de la boucle for (int i = 0; i < deplacementMin; i++) : 


 1. le calcul de nombre d'itérations 
 nb d'itérations = ( deplacementMin -1 - 0 +1 )/1 = deplacementMin = (2^n) - 1


 2.le calcul du nombre de comparaisons 
 int i = 0 -> 1op 
 2^n -1 comparaison + la comparaison de la sortie de la boucle pour => 2^n comparaison
 i <- i+ 1 ; 2op (addition + affectation) => le total égale à 2*((2^n)-1) = 2^(n+1) - 2


 3.le calcul de la complexité du plus grand bloc if else (if indic == 1)
 on remarque que les deux blocs sont équivalents dans le nombre d'instructions donc choisit l'un des deux blocs
 => calcul de la complexité du bloc if 


 if (indic == 1 ) => 1op (comparaison)
 on a 3 blocs , le bloc de if (i%3==0) , aprés le bloc else if (i%3==1),aprés le bloc else (i%3==2),aprés le bloc else
 
 donc la complexité du bloc if (indic ==1) égale à la complexité de la condition if(i%3==0) + le max (B1,B2)=B2
 dans B2 on choisit l'un des deux blocs B2' ou B2'' => B2'


---> calcul du complexité du Bloc B2'
 ---> calcul de la complexité du bloc if(i%3==1)
 if (i%3==1) -> 2op (le mod + la comparaison avec le un )
 on a deux blocs , le bloc if et le bloc else , les deux blocs ont le même nombre d'instructions 
 donc on choisit l'un des deux blocs => bloc if 

  if (!vide(p1) && (vide(p3) || sommet(p1) < sommet(p3))) --> 
 1....sommet (p1) -> 1 op (on accede au sommet du pile p1 et on le retourne)
 2....sommet (p3) -> 1 op (on accede au sommet du pile p3 et on le retourne)
 3.... sommet (p1) < sommet(p3) -> 1op (comparaison)
 4.... (vide (p3) <=> vide (p3)== 1) -> 2op (comparaison du sommet du pile avec le - 1 + le retour de la fonction )
 5....  4||3 -> 1 op (opération du ou)
 6....(!vide(p3)<=>vide(p3)!=1) -> 2op (comparaison du sommet du pile avec le - 1 + le retour de la fonction )
 7.... 6&&5 -> 1op (opération du et )


  empiler(p3, depiler(p1)) -> 
  dépiler(p1)-> 2op (accés a la pile et décrementation du sommet)
  empiler(p3,dépiler(p1))-> 2op (accés a la pile et incrémentation du sommet + affectation du résultat de dépilement du p2)

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
- le total = 1 + 3 + n+2 + 1 + 2^n + (2^(n+1))-2  + ((2^n)-1)*(1+2+2+1+1+1+2+1+2+1+2+2) = n+5+2^n+(2^(n+1)) + ( (2^n)-1 ) *(18)) = n+5+2^n+(2^n)*2 + (18*2^n -18) = 
n+5+21*2^n -18 = 21* 2^n + n -13    
- comme 2^n > n quelque soit n>=0 donc on garde seulement le plus grand coefficient qui est 2^n ce qui implique que la complexité égale à O(2^n)                        -
------------------------------------------------------------------------------------------------------------------------------------------------------------------------- 
*/
int pileDecroissante(Pile *p) {
    int x = depiler(p);//1op, 
    while (p->sommet != -1) { 
        int next = depiler(p);//2op de dépilement +1op de la vérification
        if (next < x)// 1op 
         {
            return -1;
        }
        x = next; // 1op
    }
    return 1; //1op
}

// la fonction de la vérification 
int verif_iterative(Pile A,Pile B,Pile C)
{
    if (vide(&A)&&vide(&B)&&pileDecroissante(&C))
    {
        return 1 ;
    }
    else
    {
        return -1 ; 
    }
}


/***********Pseudo code de la vérification***************/
/*
Fonction verif_iterative(Pile A,Pile B,Pile C):entier

Début
si ((vide(A)=1)et(vide(B)=1)et(pileDecroissante(C)=1) alors
    retourner (1) ; 
sinon 
    retourner (-1);
Fsi;

Fin.

*/

/*******Complexité théorique de la fonction verif_iterative************/
/*Calculons la complexité du bloc if else 
if (vide(&A)&&vide(&B)&&pileDecroissante(&C))
{
return 1;}
->
1.... (vide (&A) <=> vide (&A)== 1) -> 2op (comparaison du sommet du pile avec le - 1 aprés comparaison du retour de fonction avec 1 )
2.... (vide(&B) <=> vide (&B)== 1) -> 2op (comparaison du sommet du pile avec le - 1 aprés comparaison du retour de fonction avec 1 )
3.... deux opération du et -> 2op
4....calcul de la complexité de la fonction (pileDecroissante(&C))->
---int x = depiler(p) -> 1op (accés a la pile et décrementation du sommet)
---while (p->sommet!=-1) <=> while (!vide(p)) donc on a  dépilé tous les n éléments de la pile ce qui implique que le nombre d'itérations égale à n 
-> calcul de la complexité de la boucle while 
(n+1) vérification de (p->sommet!=-1) 
int next = dépiler(p) -> 2op * n de dépilement + n affectation -> 3n 
le pire cas c'est que chaque fois le next > x donc :
la vérification de next < x -> (1op *n)
x = next -> 1op * n 
return 1 -> 1op 

=> le total = n+1+3n+n+1+n = 6n+2

5. return 1 ; -> 1op 
donc la complexité du bloc if égale a  : 2+2+2+6n+2+1 = 6n+9

d'où la complexité total de la fonction = 6n+9 => O(n)





/*****Complexité spatial*****/
//1.vérification
/**Comme on vérifie que la pile A et B sont vides ainsi on vérifie que la pile C est remplie dans l'ordre décroissant donc on réserve une espace mémoire
pour les 3 piles de taille n (nombre de disques)+ la taille réservé pour la variable next et x (dans la fonction piledécroissante) ce qui implique que complexité spatiale = 3n+2 => O(n)
donc on octets c'est (3n+2)*4octets car chaque entier est representé en 4octets*/ 
//2.exécution
/**On fait les déplacements entre les 3 piquets donc on réserve une espace mémoire pour les 3 piles de taille n + la variable indic + la variable n +la variable i +la variable déplacementMin =>
 3n+1+1+1+1 = 3n+4 => O(n) en octets c'est (3n+4)*4octets car un entier est représenté en 4octets */




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
    printf("-----------------------------------------\n");
    printf("l'état des piquets avant le déplacement : \n");
    printf("-----------------------------------------\n");
    afficherPiquets(&p1,&p2,&p3);
    printf("-----------------------------------------\n");
    printf("l'état des piquets aprés le déplacement : \n");
   //  le plus grand disque a comme numéro n , aprés le disque le moins grand c'est  n-1 et ainsi de suite ...
    
    //pour calculer le temps de la résolution 
    start=clock();   
    resolutionIteratif(&p1, &p2, &p3, n);
    end=clock();
    float time=(float)(end-start)/CLOCKS_PER_SEC;
    printf("\t\tLe temps d'execution est : %f\n\n",time);
    start=clock();

    //la vérification de la résolution 
   if (verif_iterative(p1,p2,p3)==1)
    {
    printf("les tours de hanoi sont résolues , vérification terminée."); 
    }
    else
    {
    printf("les tours de hanoi ne  sont pas  résolues , vérification terminée.");
    }
    end=clock();
    float time2=(float)(end-start)/CLOCKS_PER_SEC;
    printf("\nLe temps de vérification est : %f\n\n",time2);
    return 0;

}
