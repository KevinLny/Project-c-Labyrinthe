/**
 * @file gameSDL.h
 * @brief Fonctions d'affichage pour le projet Labyrinthe.
 *
 * Ce fichier contient les déclarations des fonctions nécessaires pour afficher
 * le plateau de jeu, les joueurs et leurs scores dans la console.
 */

#ifndef GAMESDL_H
#define GAMESDL_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdlib.h>
#include <SDL2/SDL_ttf.h>

#include "../include/structures.h"
#include "../include/plateau.h"
#include "../include/game.h"
#include "../include/joueur.h"
#include "../include/utils.h"

#include "SDLplateau.h"
#include "affichageSDL.h"
#include "texte.h"

typedef enum {
    MENU,
    INIT_LABYRINTHE,
    JEU,
    QUIT
} GameState;

 /**
  * @brief Affiche le plateau de jeu dans la console.
  *
  * Cette fonction représente graphiquement le plateau et ses tuiles en affichant
  * leur contenu. Elle montre aussi les flèches pour indiquer les zones mobiles.
  *
  * @param n La taille du labyrinthe.
  * @param labyrinthe La matrice représentant le labyrinthe.
  */
GameState gameSDL(SDL_Renderer *renderer, SDL_Window *window, int labyrinthe[TAILLE_PLATEAU][TAILLE_PLATEAU], Joueur *joueur, int nb_joueur, int nb_tresors);

/**
  * @brief Affiche le plateau de jeu dans la console.
  *
  * Cette fonction représente graphiquement le plateau et ses tuiles en affichant
  * leur contenu. Elle montre aussi les flèches pour indiquer les zones mobiles.
  *
  * @param n La taille du labyrinthe.
  * @param labyrinthe La matrice représentant le labyrinthe.
  */
GameState lancerLabyrinthe(SDL_Renderer *renderer, SDL_Window *window, Joueur *joueurs, int nb_joueurs, int labyrinthe[TAILLE_PLATEAU][TAILLE_PLATEAU], int nb_tresors);

 /**
  * @brief Affiche le plateau de jeu dans la console.
  *
  * Cette fonction représente graphiquement le plateau et ses tuiles en affichant
  * leur contenu. Elle montre aussi les flèches pour indiquer les zones mobiles.
  *
  * @param n La taille du labyrinthe.
  * @param labyrinthe La matrice représentant le labyrinthe.
  */
GameState boucleMenu(SDL_Renderer *pRenderer, SDL_Window *window, Joueur *joueur, SDL_Texture* background, TTF_Font* font, int* nb_joueurs, int* nb_tresors);
#endif
