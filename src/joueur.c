#include <stdio.h>
#include <string.h>
#include "../include/affichage.h"
#include "../include/plateau.h"
#include "../include/structures.h"

void initJoueurs(int nbJoueurs, Joueur *joueurs, int labyrinthe[TAILLE_PLATEAU][TAILLE_PLATEAU]) {
    // Initialisation des pseudos et scores
    for (int i = 0; i < nbJoueurs; i++) {
        joueurs[i].nbTresors = 0;
        //printf("Entrez le pseudo du joueur %d : ", i + 1);
        //fgets(joueurs[i].username, MAX_USERNAME, stdin);
        joueurs[i].username[strcspn(joueurs[i].username, "\n")] = '\0';  // Supprime le \n
    }

    // Coordonnées de départ possibles pour 4 joueurs
    int positions[4][2] = {
        {1, 1},
        {1, TAILLE_PLATEAU - 2},
        {TAILLE_PLATEAU - 2, 1},
        {TAILLE_PLATEAU - 2, TAILLE_PLATEAU - 2}
    };

    // Positionnement des joueurs sur le labyrinthe
    for (int i = 0; i < nbJoueurs; i++) {
        joueurs[i].x = joueurs[i].x_init = positions[i][0];
        joueurs[i].y = joueurs[i].y_init = positions[i][1];
        labyrinthe[joueurs[i].x][joueurs[i].y] = i + 2;  // 2 à 5 selon le joueur
    }
}

void deplacerJoueur(Joueur* joueur, int tour_du_joueurx, int labyrinthe[TAILLE_PLATEAU][TAILLE_PLATEAU], int x, int y) {
    int temp = labyrinthe[joueur[tour_du_joueurx].x][joueur[tour_du_joueurx].y];
    labyrinthe[joueur[tour_du_joueurx].x][joueur[tour_du_joueurx].y] = 1; // case vidée
    labyrinthe[x][y] = temp;
    joueur[tour_du_joueurx].x = x;
    joueur[tour_du_joueurx].y = y;
}

void joueurSurTresor(Joueur* joueurs, int tour_du_joueurx, int labyrinthe[TAILLE_PLATEAU][TAILLE_PLATEAU]) {
    joueurs[tour_du_joueurx].nbTresors += 1;
    printf("Le joueur %s a trouvé un trésor ! Score: %d\n", joueurs[tour_du_joueurx].username, joueurs[tour_du_joueurx].nbTresors);
    placer_tresors(labyrinthe, 1); // Replace un trésor
}
