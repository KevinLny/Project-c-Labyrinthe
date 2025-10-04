/*!\file game.h
 *  \brief Fonctions principales du jeu Labyrinthe.
 *
 *  Ce fichier contient les fonctions de gestion du tour de jeu, de la boucle principale du jeu,
 *  de la détection de victoire, de l’analyse des commandes et de l’affichage des règles.
 */

#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include "structures.h"

/**
 * \brief Analyse une commande entrée par l'utilisateur.
 *
 * Cette fonction interprète une commande textuelle et extrait les paramètres si nécessaire.
 *
 * \param input La chaîne de caractères représentant la commande.
 * \return Une structure CommandeAnalyse contenant le type de commande et ses arguments.
 */
CommandeAnalyse analyser_commande(const char *input);

/**
 * \brief Affiche les règles du jeu et les commandes disponibles.
 */
void afficher_regles();

/**
 * \brief Vérifie si un joueur a gagné la partie.
 *
 * Un joueur gagne s’il a récupéré tous ses trésors et est revenu à sa position de départ.
 *
 * \param joueurs Tableau des joueurs.
 * \param nb_joueur Nombre de joueurs.
 * \param nb_tresors Nombre de trésors à collecter.
 * \return true si un joueur a gagné, false sinon.
 */
bool winner(Joueur* joueurs, int nb_joueur, int nb_tresors);

/**
 * \brief Lance la boucle principale du jeu.
 *
 * Initialise le jeu, gère les tours de chaque joueur et affiche le gagnant à la fin.
 */
void game();

/**
 * \brief Demande à l'utilisateur le nombre de joueurs.
 *
 * Effectue une vérification pour s’assurer que l’entrée est correcte.
 *
 * \return Le nombre de joueurs choisi par l’utilisateur.
 */
int demander_nombre_joueurs();

/**
 * \brief Demande à l'utilisateur le nombre de trésors à collecter pour gagner.
 *
 * Effectue une vérification pour s’assurer que l’entrée est correcte.
 *
 * \return Le nombre de trésors choisi par l’utilisateur.
 */
int demander_nombre_tresors();

/**
 * \brief Gère les actions d’un joueur pendant son tour.
 *
 * Cette fonction permet au joueur courant d'effectuer ses actions : placer une tuile, se déplacer,
 * consulter le plateau ou terminer son tour.
 *
 * \param joueur Tableau de joueurs.
 * \param tour_du_joueur Pointeur vers l’indice du joueur courant.
 * \param nb_joueur Nombre total de joueurs.
 * \param nb_tresors Nombre de trésors nécessaires pour gagner.
 * \param labyrinthe Plateau de jeu.
 */
void gerer_tour(Joueur joueur[], int *tour_du_joueur, int nb_joueur, int nb_tresors, int labyrinthe[TAILLE_PLATEAU][TAILLE_PLATEAU]);

/**
 * \brief Traite une commande saisie par l’utilisateur pendant un tour.
 *
 * Effectue les actions correspondant à la commande analysée.
 *
 * \param cmd La commande analysée.
 * \param joueur Tableau des joueurs.
 * \param tour_du_joueur_x Pointeur vers l’indice du joueur courant.
 * \param nb_joueur Nombre total de joueurs.
 * \param labyrinthe Plateau de jeu.
 * \param a_deplace Booléen indiquant si le joueur s’est déjà déplacé ce tour.
 * \param a_place_tuile Booléen indiquant si le joueur a déjà placé une tuile ce tour.
 * \param tour_termine Booléen à mettre à true pour terminer le tour.
 */
void traiter_commande(CommandeAnalyse cmd, Joueur joueur[], int *tour_du_joueur_x, int nb_joueur, int labyrinthe[TAILLE_PLATEAU][TAILLE_PLATEAU], bool *a_deplace, bool *a_place_tuile, bool *tour_termine);

#endif /* GAME_H */
