#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/affichage.h"

void afficher_labyrinthe(int n, int labyrinthe[TAILLE_PLATEAU][TAILLE_PLATEAU]) {
    if (n < 2) {
        printf("La taille du labyrinthe doit être au moins 2.\n");
        return;
    }

    // Affichage des flèches pour la tuile mobile
    int sum = 1;
    printf("   ");
    for (int i = 0; i < n-2; i++) {
        if (i != 0 && i % 2 == 0) {  // Vérifie si (i+1) est impair
            printf("%i ", sum);
            sum++;
        }
        else{
            printf("  ");
        }
    }
    printf("\n   ");
    for (int i = 0; i < n-2; i++) {
        if (i != 0 && i % 2 == 0) {  // Affiche des barres verticales
            printf("↓ ");
        }
        else{
            printf("  ");
        }
    }

    // Affichage du Labyrinthe
    for (int i = 0; i < n; i++) {
        if(i != 0 && i % 2 == 0 && i != n-1){
            printf("\n%i→ ", sum);
            sum++;
        }
        else{
            printf("\n   ");
        }
        for (int j = 0; j < n; j++) {
            if (labyrinthe[i][j] == 1){
                printf("%c ", CHEMIN);
            }  // Case accessible
            if (labyrinthe[i][j] == 0){
                printf("%c ", MUR);
            }  // Mur
            if (labyrinthe[i][j] == 2){
                printf(ROUGE "%s " RESET, PION1);
            }
            if (labyrinthe[i][j] == 3){
                printf(VERT "%s " RESET, PION2);
            }
            if (labyrinthe[i][j] == 4){
                printf(BLEU "%s " RESET, PION3);
            }
            if (labyrinthe[i][j] == 5){
                printf(JAUNE "%s " RESET, PION4);
            }
            if (labyrinthe[i][j] == 6){
                printf("T ");
            }
        }
        
    }
    printf("\n");
}

void afficher_joueurs(Joueur *joueurs,int nbjoueurs) {
    for (int i = 0; i < nbjoueurs; i++) {
        printf("Informations du Joueur %d:\n ", i+1);
        printf("- Pseudo Joueurs %d : %s \n ",i+1 , joueurs[i].username);
        printf("- position Joueur %s : x = %d et y =%d \n" , joueurs[i].username, joueurs[i].x , joueurs[i].y);
        printf("- nombre des tresors trouvee par le Joueurs : %d \n" , joueurs[i].nbTresors);
  }
}
