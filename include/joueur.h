
#ifndef JOUEUR
#define JOUEUR

#include "structures.h"

/**
 * @brief Initialise les joueurs.
 *
 * Cette fonction initialise un tableau de joueurs en attribuant des positions initiales
 * et des identifiants uniques.
 *
 * @param joueurs Tableau de joueurs à initialiser.
 * @param nbJoueurs Nombre total de joueurs.
 */
void initJoueurs(int nbJoueurs, Joueur *joueurs, int labyrinthe[TAILLE_PLATEAU][TAILLE_PLATEAU]);

/**
 * @brief Déplace un joueur sur le plateau.
 *
 * Cette fonction met à jour la position d'un joueur donné en fonction des
 * nouvelles coordonnées spécifiées.
 *
 * @param joueur Pointeur vers la structure du joueur.
 * @param plateau Pointeur vers la structure du plateau.
 * @param x Nouvelle position X.
 * @param y Nouvelle position Y.
 */
void deplacerJoueur(Joueur* joueur,int nb_joueur, int labyrinthe[TAILLE_PLATEAU][TAILLE_PLATEAU], int x, int y);

/**
 * @brief Vérifie si un joueur a trouvé un trésor.
 *
 * Retourne vrai si la position actuelle du joueur correspond à celle d’un trésor.
 *
 * @param joueur Pointeur vers la structure du joueur.
 * @param plateau Pointeur vers la structure du plateau.
 * @return `true` si le joueur est sur un trésor, sinon `false`.
 */
void joueurSurTresor(Joueur* joueur, int tour_du_joueurx, int labyrinthe[TAILLE_PLATEAU][TAILLE_PLATEAU]);

#endif /* JOUEUR */