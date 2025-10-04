
/*!\file plateau.h
 *  \brief Gestion du plateau de jeu dans le projet Labyrinthe.
 *
 *  Ce fichier contient les fonctions nécessaires pour initialiser et manipuler
 *  le plateau de jeu, ainsi que pour vérifier les chemins possibles entre les tuiles.
 */

 #ifndef PLATEAU
 #define PLATEAU
 
 #include "structures.h"

 /**
  * \brief Initialise le plateau de jeu.
  *
  * Cette fonction configure le plateau en plaçant des tuiles aléatoires dans la grille
  * et initialise la tuile mobile.
  *
  * \param Taille du plateau.
  * \param plateau Un pointeur vers la structure du plateau à initialiser.
  */
 void init_plateau(int n, int labyrinthe[TAILLE_PLATEAU][TAILLE_PLATEAU]);
 
 /**
  * \brief Gère le glissement des tuiles sur le plateau.
  *
  * Cette fonction permet de glisser la tuile mobile dans une ligne ou une colonne
  * du plateau dans une direction donnée.
  *
  * \param sur le plateau il y a des chiffres de 1 à 6 ce sont les endroit ou la tuile peut être placé.
  * \param Sens = 0 gauche/haut sens = 1 droite/bas
  * \param tuile = 0 pour un mur et tuile = 1 pour un chemin
  * \return Renvoie 1 si tout c'est bien passé, 0 sinon.
  */
 int glisser_tuile(int numero, int sens, int tuile, int labyrinthe[TAILLE_PLATEAU][TAILLE_PLATEAU], Joueur joueurs[], int nb_joueurs);
 
 /**
 * \brief Place aléatoirement des trésors sur le plateau de jeu.
 *
 * Cette fonction tente de placer un nombre spécifié de trésors (valeur 6) dans le labyrinthe,
 * uniquement sur des cases accessibles (valeur 1) et qui ne correspondent pas aux positions
 * de départ des joueurs (coins du plateau). Les trésors sont placés de manière aléatoire
 * à l’intérieur de la zone jouable du plateau (hors bordure).
 *
 * \param labyrinthe Un tableau 2D représentant le plateau, contenant des 0 (murs) et des 1 (chemins).
 * \param nb_tresors Le nombre de trésors à placer sur le plateau.
 * \return true si tous les trésors ont été placés avec succès, false sinon (échec du placement).
 */
 bool placer_tresors(int labyrinthe[TAILLE_PLATEAU][TAILLE_PLATEAU], int nb_tresors);

/**
 * \brief Vérifie s’il existe un chemin entre deux positions à l’aide de l’algorithme de Lee.
 *
 * Cette fonction utilise l’algorithme de Lee (BFS sur grille) pour déterminer s’il existe un
 * chemin entre la position actuelle d’un joueur et sa position d’arrivée. Le déplacement est 
 * autorisé uniquement sur des cases accessibles (valeurs 1 ou 6), en 4 directions (haut, bas, gauche, droite).
 *
 * \param labyrinthe Un tableau 2D représentant le plateau, contenant des 0 (murs), 1 (chemins) ou 6 (trésors).
 * \param joueur Une structure contenant les coordonnées de départ (x, y) et d’arrivée (x_arrivee, y_arrivee) du joueur.
 * \return La distance minimale (en nombre de déplacements) entre la position de départ et la position d’arrivée,
 *         ou -1 si aucun chemin n’existe.
 */
int est_cheminLee(int labyrinthe[TAILLE_PLATEAU][TAILLE_PLATEAU], Joueur joueur, int x, int y);


 #endif /* PLATEAU*/