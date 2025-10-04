/*!\file structures.h
 *  \brief Déclarations des structures de données principales pour le projet Labyrinthe.
 *
 *  Ce fichier contient les définitions des structures utilisées pour représenter
 *  les tuiles du labyrinthe, les joueurs et le plateau de jeu.
 */

 #ifndef STRUCTURES_H
 #define STRUCTURES_H
 
#include <stdbool.h>

#define MUR '#'
#define CHEMIN ' '
 
// Codes de couleurs ANSI pour les joueurs
#define RESET   "\033[0m"
#define ROUGE   "\033[31m"
#define VERT    "\033[32m"
#define BLEU    "\033[34m"
#define JAUNE   "\033[33m"

// Définir des icônes pour les joueurs
#define PION1 "♠"  // Pique
#define PION2 "♥"  // Cœur
#define PION3 "♦"  // Carreau
#define PION4 "♣"  // Trèfle

 /**
  * \brief Dimensions du plateau de jeu.
  *
  * TAILLE_PLATEAU définit la taille de la grille du plateau (7x7 par défaut).
  * MAX_JOUEURS indique le nombre maximal de joueurs.
  */
 #define TAILLE_PLATEAU 9 // 7x7 case du labyrinthe + 2 pour les bordures
 #define TRESORS 8
 #define MAX_JOUEURS 4
 #define MAX_USERNAME 10
 
 /**
  * \brief Structure représentant un joueur.
  *
  * Un joueur est défini par ses coordonnées sur le plateau, le nombre total
  * de trésors à collecter, et un tableau listant les trésors à trouver.
  */
 typedef struct {
     int x;           /**< Coordonnée X du joueur. */
     int y;           /**< Coordonnée Y du joueur. */
     int nbTresors;
     int x_init, y_init; // Coordonnées de départ
     char username [MAX_USERNAME] ;
 } Joueur;

 /**
  * \brief Structure utilisé pour l'algorithme de Lee.
  *
  * On créer des distances et des coordonnées en données.
  */
typedef struct {
    int x, y;
    int dist;
} Cell;

 /**
  * \brief Commande pour le joueur.
  *
  * Commande créer pour jouer?
  */
typedef enum {
    CMD_HELP,
    CMD_REGLE,
    CMD_LISTE,
    CMD_SCORE,
    CMD_SHOW,
    CMD_MOVE,
    CMD_PLACE,
    CMD_NEXT,
    CMD_QUIT,
    CMD_UNKNOWN
} Commande;

 /**
  * \brief Structure utilisé pour les commandes à arguments.
  *
  * On peut récuperer les arguments des commandes grâce à cette structure.
  */
typedef struct {
    Commande type;
    int arg1;
    int arg2;
    int arg3;
} CommandeAnalyse;


 #endif // STRUCTURES_H
 
