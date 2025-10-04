/**
 * @file affichageSDL.h
 * @brief Fonctions pour initialiser et gérer l'affichage SDL du projet Labyrinthe.
 *
 * Ce fichier contient les déclarations des fonctions nécessaires à l'initialisation et à la gestion
 * de l'affichage graphique via SDL, incluant les fenêtres, textures, boutons, et interactions utilisateur.
 */

#ifndef AFFICHAGESDL_H
#define AFFICHAGESDL_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <SDL2/SDL_ttf.h>

#include "SDLplateau.h"
#include "affichageSDL.h"
#include "gameSDL.h"
#include "../include/joueur.h"
#include "../include/structures.h"

/**
 * \brief Initialise l'affichage SDL (fenêtre, renderer, textures, polices, sons).
 *
 * Cette fonction configure les composants essentiels pour une fenêtre SDL :
 * création de la fenêtre et du renderer, chargement des textures, des polices et du son.
 *
 * \param window Double pointeur vers la fenêtre SDL créée.
 * \param renderer Double pointeur vers le renderer SDL créé.
 * \param titre Titre affiché en haut de la fenêtre.
 * \param w Largeur de la fenêtre en pixels.
 * \param h Hauteur de la fenêtre en pixels.
 * \param background Double pointeur vers la texture utilisée comme arrière-plan.
 * \param font Double pointeur vers la police TTF chargée pour l'affichage de texte.
 * \param son Double pointeur vers le son (Mix_Chunk) chargé.
 *
 * \return 0 en cas de succès, une valeur négative en cas d'erreur.
 */
int init(SDL_Window** window, SDL_Renderer** renderer, const char* titre, int w, int h, SDL_Texture** background, TTF_Font** font);

/**
 * \brief Charge une police TTF depuis un fichier spécifié.
 *
 * \param chemin Chemin d'accès vers le fichier de police.
 * \param taille Taille de la police à charger.
 *
 * \return Un pointeur vers la structure TTF_Font chargée, ou NULL en cas d'erreur.
 */
TTF_Font* chargerPolice(const char* chemin, int taille);

/**
 * \brief Vérifie si les coordonnées spécifiées (x, y) se trouvent dans une zone rectangulaire (bouton).
 *
 * \param x Coordonnée horizontale à vérifier.
 * \param y Coordonnée verticale à vérifier.
 * \param bouton Structure SDL_Rect représentant la zone du bouton.
 *
 * \return 1 si les coordonnées sont dans le bouton, sinon 0.
 */
int bouton(int x, int y, SDL_Rect bouton);

/**
 * \brief Libère proprement les ressources SDL utilisées (renderer, fenêtre, police, musique).
 *
 * \param renderer Pointeur vers le renderer SDL à libérer.
 * \param window Pointeur vers la fenêtre SDL à libérer.
 * \param font Pointeur vers la police TTF à libérer.
 * \param musique Pointeur vers la structure Mix_Chunk (son) à libérer.
 */
void freeSDL(SDL_Renderer* renderer, SDL_Window* window, SDL_Texture* texture, TTF_Font* font, Mix_Chunk* musique);

/**
 * @brief Lance une animation de victoire pour le joueur gagnant.
 *
 * Cette fonction crée et affiche une animation graphique célébrant la victoire du joueur.
 *
 * @param renderer Pointeur vers le renderer SDL.
 * @param window Pointeur vers la fenêtre SDL.
 * @param joueurs Tableau des structures Joueur.
 * @param tour_du_joueur Index du joueur qui a gagné la partie.
 */
void animationVictoire(SDL_Renderer* renderer, SDL_Window* window, Joueur* joueurs, int tour_du_joueur);

#endif

