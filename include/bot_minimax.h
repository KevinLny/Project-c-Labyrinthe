/*!
 * \file bot.h
 * \brief IA pour le joueur contrôlé par un bot utilisant l'algorithme Minimax.
 *
 * Ce fichier contient les fonctions nécessaires pour que le bot prenne des décisions
 * optimales dans une partie en 1 contre 1 dans le jeu de labyrinthe.
 * Le bot analyse les coups possibles à l’aide de l’algorithme Minimax avec évaluation heuristique.
 */

 #ifndef BOT_H
 #define BOT_H
 
 #include "structures.h"
 
 
 /**
  * \brief Calcule le meilleur coup pour le bot en utilisant l'algorithme Minimax.
  *
  * Cette fonction explore récursivement les différents coups possibles du bot et de l’adversaire
  * jusqu'à une profondeur définie, et choisit le meilleur mouvement pour le bot selon une fonction d’évaluation.
  *
  * \param labyrinthe Le plateau de jeu actuel.
  * \param joueur_bot Le bot (joueur IA).
  * \param joueur_adv L’adversaire humain.
  * \param profondeur La profondeur maximale d'exploration du Minimax.
  * \param est_maximisant true si c’est le tour du bot, false si c’est celui de l’adversaire.
  * \return Une structure contenant le meilleur score et le mouvement associé.
  */
 int minimax(int labyrinthe[TAILLE_PLATEAU][TAILLE_PLATEAU], Joueur joueur_bot, Joueur joueur_adv, int profondeur, bool est_maximisant);
 
 /**
  * \brief Évalue l'état du jeu pour le bot.
  *
  * Cette fonction renvoie une valeur numérique représentant la qualité de la position actuelle
  * pour le bot. Elle peut prendre en compte la distance au trésor, la proximité de l’adversaire, etc.
  *
  * \param labyrinthe Le plateau de jeu.
  * \param joueur_bot Le bot.
  * \param joueur_adv L’adversaire.
  * \return Un score heuristique représentant l’avantage du bot.
  */
 int evaluer_etat(int labyrinthe[TAILLE_PLATEAU][TAILLE_PLATEAU], Joueur joueur_bot, Joueur joueur_adv);
 
 /**
  * \brief Applique un mouvement au plateau pour simuler un tour.
  *
  * Cette fonction met à jour les positions des joueurs ou modifie la configuration
  * du plateau (par exemple, glisser une tuile ou déplacer un joueur).
  *
  * \param labyrinthe Le plateau de jeu.
  * \param joueur Le joueur à déplacer.
  * \param mouvement Le mouvement à appliquer.
  */
 //void appliquer_mouvement(int labyrinthe[TAILLE_PLATEAU][TAILLE_PLATEAU], Joueur* joueur, Mouvement mouvement);
 
 /**
  * \brief Annule un mouvement précédemment appliqué (utile pour le Minimax).
  *
  * Cette fonction restaure l'état précédent du plateau et du joueur,
  * afin de tester d’autres branches de l’arbre Minimax.
  *
  * \param labyrinthe Le plateau de jeu.
  * \param joueur Le joueur à rétablir.
  * \param mouvement Le mouvement à annuler.
  */
 //void annuler_mouvement(int labyrinthe[TAILLE_PLATEAU][TAILLE_PLATEAU], Joueur* joueur, Mouvement mouvement);
 
 /**
  * \brief Fonction principale appelée pendant le tour du bot.
  *
  * Cette fonction utilise Minimax pour choisir le meilleur coup et l’exécute.
  *
  * \param labyrinthe Le plateau de jeu.
  * \param joueur_bot Le joueur contrôlé par l'IA.
  * \param joueur_adv Le joueur humain.
  */
 void jouer_tour_bot(int labyrinthe[TAILLE_PLATEAU][TAILLE_PLATEAU], Joueur* joueur_bot, Joueur joueur_adv);
 
 #endif /* BOT_H */
 