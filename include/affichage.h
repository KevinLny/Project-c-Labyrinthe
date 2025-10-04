 #ifndef AFFICHAGE_H
 #define AFFICHAGE_H
 
 #include "structures.h"
 
/**
 * @file affichage.h
 * @brief Fonctions d'affichage pour le projet Labyrinthe.
 *
 * Ce fichier contient les déclarations des fonctions nécessaires pour afficher
 * le plateau de jeu, les joueurs et leurs scores dans la console.
 */

 /**
  * @brief Affiche le plateau de jeu dans la console.
  *
  * Cette fonction représente graphiquement le plateau et ses tuiles en affichant
  * leur contenu. Elle montre aussi les flèches pour indiquer les zones mobiles.
  *
  * @param n La taille du labyrinthe.
  * @param labyrinthe La matrice représentant le labyrinthe.
  */
 void afficher_labyrinthe(int n, int labyrinthe[TAILLE_PLATEAU][TAILLE_PLATEAU]);
 
 /**
  * @brief Affiche les pseudos, positions et scores des joueurs.
  *
  * Cette fonction affiche les informations principales des joueurs dans la console.
  *
  * @param joueurs Tableau contenant les joueurs.
  * @param nbjoueurs Nombre total de joueurs.
  */
 void afficher_joueurs(Joueur *joueurs, int nbjoueurs);
 
 #endif /* AFFICHAGE_H */
 