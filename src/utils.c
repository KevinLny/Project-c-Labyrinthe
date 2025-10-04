#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../include/structures.h"

void afficher_matrice(int labyrinthe[TAILLE_PLATEAU][TAILLE_PLATEAU]){
    printf("\n");
    for(int i=0; i<TAILLE_PLATEAU; i++){
        for(int j=0; j<TAILLE_PLATEAU; j++){
            printf(" %d ", labyrinthe[i][j]);
        }
        printf("\n");
    }
}