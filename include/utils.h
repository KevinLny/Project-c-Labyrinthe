/*!\file utils.h
 *  \brief Fonctions utilitaires pour le projet Labyrinthe.
 *
 *  Ce fichier contient des fonctions utiles pour la génération de nombres
 *  aléatoires et la manipulation des trésors dans le jeu.
 */

 #ifndef UTILS
 #define UTILS
 
 #include "structures.h"
 
 /**
  * \brief Affiche la matrice du labyrinthe.
  *
  * Cette fonction sert principalement au debug. 
  *
  * \param La matrice du labyrinthe.
  */
 void afficher_matrice(int labyrinthe[TAILLE_PLATEAU][TAILLE_PLATEAU]);
 
 #endif /* UTILS*/