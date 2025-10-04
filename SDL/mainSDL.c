#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

#include "affichageSDL.h"
#include "texte.h"
#include "gameSDL.h"
#include "../include/joueur.h"
#include "../include/structures.h"
#include "../include/plateau.h"

int main(int argc, char *argv[]) {
    SDL_Window *window   = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Texture* background = NULL;
    TTF_Font* font = NULL;

    // initialisation SDL, TTF, Mixer, window, renderer, etc.
    init(&window, &renderer, "Le Labyrinthe", 1100, 800, &background, &font);
	
    int labyrinthe[TAILLE_PLATEAU][TAILLE_PLATEAU];
    Joueur joueurs[MAX_JOUEURS];
    int nb_joueurs = 0;
    int nb_tresors = 0;
    GameState etat = MENU;

    while (etat != QUIT) {
        switch (etat) {
            case MENU:
                // affiche le menu, remplit nb_joueurs, nb_tresors…
                etat = boucleMenu(renderer, window, joueurs, background, font, &nb_joueurs, &nb_tresors);
                break;

            case INIT_LABYRINTHE:
                //construit le labyrinthe et les joueurs
                etat = lancerLabyrinthe(renderer, window, joueurs, nb_joueurs, labyrinthe, nb_tresors);
                break;

            case JEU:
                // lance la boucle de jeu
                etat = gameSDL(renderer, window, labyrinthe, joueurs, nb_joueurs, nb_tresors);
                break;

            default:
                etat = QUIT;
                break;
        }
    }

    // nettoyage
    freeSDL(renderer, window, background, font, NULL);
    return 0;
}
