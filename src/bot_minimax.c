#include <stdio.h>
#include <limits.h>
#include "../include/plateau.h"
#include "../include/joueur.h"
#include "../include/utils.h"

typedef struct {
    int ligne;
    int colonne;
    int direction;
    int cibleX;
    int cibleY;
    int score;
} ActionBot;

#define MAX_DEPTH 2

int evaluer_plateau(Joueur bot, int lab[TAILLE_PLATEAU][TAILLE_PLATEAU]) {
    // Exemple simple : moins la distance au trésor est grande, meilleur c’est
    int meilleur_score = -1000;

    for (int i = 0; i < TAILLE_PLATEAU; i++) {
        for (int j = 0; j < TAILLE_PLATEAU; j++) {
            if (lab[i][j] == 6) { // Case trésor
                int dist = est_cheminLee(lab, bot, i, j);
                if (dist > 0) {
                    int score = 100 - dist;
                    if (score > meilleur_score) meilleur_score = score;
                }
            }
        }
    }

    return meilleur_score;
}

int minimax(Joueur* joueurs, int joueur_actuel, int profondeur, int maxPlayer, int lab[TAILLE_PLATEAU][TAILLE_PLATEAU]) {
    if (profondeur == 0 || winner(joueurs, 2, joueurs[joueur_actuel].nbTresors + 1)) {
        return evaluer_plateau(joueurs[0], lab); // Joueur 0 = le bot
    }

    int meilleur_score = maxPlayer ? INT_MIN : INT_MAX;
    int directions[4] = {0, 1, 2, 3};
    int indices_valides[3] = {2, 4, 6};

    for (int ligne = 0; ligne < TAILLE_PLATEAU; ligne++) {
        for (int colonne = 0; colonne < TAILLE_PLATEAU; colonne++) {
            if ((ligne == 2 || ligne == 4 || ligne == 6) || (colonne == 2 || colonne == 4 || colonne == 6)) {
                for (int d = 0; d < 4; d++) {
                    // Simulation : copier le plateau
                    int copie_lab[TAILLE_PLATEAU][TAILLE_PLATEAU];
                    memcpy(copie_lab, lab, sizeof(copie_lab));
                    Joueur copie_joueurs[2];
                    memcpy(copie_joueurs, joueurs, sizeof(copie_joueurs));

                    if (!glisser_tuile(ligne, colonne, directions[d], copie_lab, copie_joueurs, 2)) continue;

                    // Essayer de déplacer le joueur vers un trésor
                    for (int i = 0; i < TAILLE_PLATEAU; i++) {
                        for (int j = 0; j < TAILLE_PLATEAU; j++) {
                            if (copie_lab[i][j] == 6 && est_cheminLee(copie_lab, copie_joueurs[joueur_actuel], i, j) > 0) {
                                deplacerJoueur(copie_joueurs, joueur_actuel, copie_lab, i, j);
                                joueurSurTresor(copie_joueurs, joueur_actuel, copie_lab);

                                int score = minimax(copie_joueurs, 1 - joueur_actuel, profondeur - 1, !maxPlayer, copie_lab);

                                if (maxPlayer) meilleur_score = score > meilleur_score ? score : meilleur_score;
                                else           meilleur_score = score < meilleur_score ? score : meilleur_score;
                            }
                        }
                    }
                }
            }
        }
    }

    return meilleur_score;
}

ActionBot bot_choisir_action(Joueur* joueurs, int lab[TAILLE_PLATEAU][TAILLE_PLATEAU]) {
    ActionBot meilleure_action = {-1, -1, -1, -1, -1, INT_MIN};
    int directions[4] = {0, 1, 2, 3};
    int indices_valides[3] = {2, 4, 6};

    for (int l = 0; l < TAILLE_PLATEAU; l++) {
        for (int c = 0; c < TAILLE_PLATEAU; c++) {
            if ((l == 2 || l == 4 || l == 6) || (c == 2 || c == 4 || c == 6)) {
                for (int d = 0; d < 4; d++) {
                    int copie_lab[TAILLE_PLATEAU][TAILLE_PLATEAU];
                    memcpy(copie_lab, lab, sizeof(copie_lab));
                    Joueur copie_joueurs[2];
                    memcpy(copie_joueurs, joueurs, sizeof(copie_joueurs));

                    if (!glisser_tuile(l, c, directions[d], copie_lab, copie_joueurs, 2)) continue;

                    for (int i = 0; i < TAILLE_PLATEAU; i++) {
                        for (int j = 0; j < TAILLE_PLATEAU; j++) {
                            if (copie_lab[i][j] == 6 && est_cheminLee(copie_lab, copie_joueurs[0], i, j) > 0) {
                                deplacerJoueur(copie_joueurs, 0, copie_lab, i, j);
                                joueurSurTresor(copie_joueurs, 0, copie_lab);

                                int score = minimax(copie_joueurs, 1, MAX_DEPTH - 1, 0, copie_lab);
                                if (score > meilleure_action.score) {
                                    meilleure_action.ligne = l;
                                    meilleure_action.colonne = c;
                                    meilleure_action.direction = directions[d];
                                    meilleure_action.cibleX = i;
                                    meilleure_action.cibleY = j;
                                    meilleure_action.score = score;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return meilleure_action;
}
