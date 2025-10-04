/**
 * @file SDLplateau.h
 * @brief Fonctions d'affichage et de gestion graphique pour le projet Labyrinthe.
 *
 * Ce fichier contient les déclarations des fonctions nécessaires pour afficher
 * graphiquement le plateau de jeu, gérer les menus et les interactions utilisateurs.
 */

#ifndef SDLPLATEAU_H
#define SDLPLATEAU_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "../include/structures.h"
#include "../include/plateau.h"
#include "../include/game.h"
#include "../include/joueur.h"
#include "texte.h"


#define NB_BOUTONS 12
#define CASE_TAILLE 120

/**
  * \brief Structure utilisé pour utiliser les flèches en tant que bouton.
  *
  * Chaque flèche possède un numéro, un sens, une position et une taille.
  */
typedef struct {
  SDL_Rect rect;      // Position et taille du bouton (flèche)
  int numero;         // Numéro (1 à 6)
  int sens;           // Sens (0 ou 1)
  int est_rouge;
} BoutonFleche;

/**
 * @brief Initialise les boutons fléchés pour l'interaction utilisateur.
 *
 * Cette fonction prépare les zones interactives correspondant aux flèches qui permettent
 * de déplacer des lignes ou colonnes du labyrinthe.
 *
 * @param window Pointeur vers la fenêtre SDL.
 * @param boutons Tableau des boutons fléchés à initialiser.
 */
void initialiser_boutons_fleches(SDL_Window* window, BoutonFleche* boutons);

/**
 * @brief Affiche les flèches directionnelles et initialise leur état selon la position de la souris.
 *
 * Cette fonction affiche visuellement les boutons fléchés sur l'écran et les met en surbrillance
 * si la souris passe au-dessus.
 *
 * @param renderer Pointeur vers le renderer SDL.
 * @param flecheTexture Texture des flèches normales.
 * @param flecheTextureRouge Texture des flèches en surbrillance (rouges).
 * @param boutons Tableau des boutons fléchés à afficher.
 * @param mouse_x Coordonnée x actuelle de la souris.
 * @param mouse_y Coordonnée y actuelle de la souris.
 */
void afficher_fleches_et_initialiser_boutons(SDL_Renderer* renderer, SDL_Texture* flecheTexture, SDL_Texture* flecheTextureRouge, BoutonFleche* boutons, int mouse_x, int mouse_y);

/**
 * @brief Affiche le labyrinthe dans la fenêtre SDL.
 *
 * Cette fonction dessine graphiquement l'état actuel du labyrinthe, y compris ses cases,
 * murs et trésors, en tenant compte de la position de la souris pour les interactions potentielles.
 *
 * @param n Taille du labyrinthe.
 * @param labyrinthe Matrice représentant le plateau du jeu.
 * @param renderer Pointeur vers le renderer SDL.
 * @param window Pointeur vers la fenêtre SDL.
 * @param mouse_x Coordonnée x actuelle de la souris.
 * @param mouse_y Coordonnée y actuelle de la souris.
 */
void afficher_labyrintheSDL(int n, int labyrinthe[TAILLE_PLATEAU][TAILLE_PLATEAU], SDL_Renderer* renderer, SDL_Window* window, int mouse_x, int mouse_y);

/**
 * @brief Affiche l'image d'arrière-plan dans la fenêtre SDL.
 *
 * Cette fonction charge et affiche une texture d'arrière-plan sur la totalité de la fenêtre.
 *
 * @param renderer Pointeur vers le renderer SDL.
 * @param window Pointeur vers la fenêtre SDL.
 */
void affichage_background(SDL_Renderer* renderer, SDL_Window* window);

/**
 * @brief Vérifie si un clic de souris est effectué sur une case du labyrinthe et retourne ses coordonnées.
 *
 * @param n Taille du labyrinthe.
 * @param window Pointeur vers la fenêtre SDL.
 * @param mouse_x Coordonnée x du clic de la souris.
 * @param mouse_y Coordonnée y du clic de la souris.
 * @param ligne Pointeur vers la ligne de la case cliquée (résultat).
 * @param colonne Pointeur vers la colonne de la case cliquée (résultat).
 *
 * @return true si une case a été cliquée, false sinon.
 */
bool caseCliquee(int n, SDL_Window* window, int mouse_x, int mouse_y, int* ligne, int* colonne);

#endif