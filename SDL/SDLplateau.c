#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>

#include "SDLplateau.h"



void afficher_fleches_et_initialiser_boutons(SDL_Renderer* renderer, SDL_Texture* flecheTexture,SDL_Texture* flecheTextureRouge, BoutonFleche* boutons, int mouse_x, int mouse_y) {

	int index=0;
    for (int i = 0; i < TAILLE_PLATEAU-2; i++) {
        if (i % 2 != 0) {
            int numero = (i / 2) + 1;  // 1, 2, 3 pour les colonnes/lignes impaires
			int offset_y = 120;
			int offset_x = 280;
            // Flèche en haut (descend) - sens 0
            SDL_Rect haut = {
                offset_x + i * CASE_TAILLE,
                offset_y - CASE_TAILLE,
                CASE_TAILLE,
                CASE_TAILLE
            };
			int est_rouge_haut = SDL_PointInRect(&(SDL_Point){mouse_x, mouse_y}, &haut);
			SDL_Texture* texHaut = SDL_PointInRect(&(SDL_Point){mouse_x, mouse_y}, &haut) ? flecheTextureRouge : flecheTexture;
            SDL_RenderCopyEx(renderer, texHaut, NULL, &haut, -270, NULL, SDL_FLIP_NONE);
            boutons[index++] = (BoutonFleche){haut, numero, 0,est_rouge_haut};            // Flèche en bas (monte) - sens 1
            SDL_Rect bas = {
                offset_x + i * CASE_TAILLE,
                offset_y + (TAILLE_PLATEAU-2) * CASE_TAILLE,
                CASE_TAILLE,
                CASE_TAILLE
            };
			int est_rouge_bas = SDL_PointInRect(&(SDL_Point){mouse_x, mouse_y}, &bas);
			SDL_Texture* texBas = SDL_PointInRect(&(SDL_Point){mouse_x, mouse_y}, &bas) ? flecheTextureRouge : flecheTexture;
            SDL_RenderCopyEx(renderer, texBas, NULL, &bas, 270, NULL, SDL_FLIP_NONE);
            boutons[index++] = (BoutonFleche){bas, numero, 1,est_rouge_bas};

            // Flèche à gauche (vers la droite) - sens 0
            SDL_Rect gauche = {
                offset_x - CASE_TAILLE,
                offset_y + i * CASE_TAILLE,
                CASE_TAILLE,
                CASE_TAILLE
            };
			int est_rouge_gauche = SDL_PointInRect(&(SDL_Point){mouse_x, mouse_y}, &gauche);
			SDL_Texture* texGauche = SDL_PointInRect(&(SDL_Point){mouse_x, mouse_y}, &gauche) ? flecheTextureRouge : flecheTexture;
            SDL_RenderCopyEx(renderer, texGauche, NULL, &gauche, 0, NULL, SDL_FLIP_NONE);
            boutons[index++] = (BoutonFleche){gauche, numero + 3, 0,est_rouge_gauche};

            // Flèche à droite (vers la gauche) - sens 1
            SDL_Rect droite = {
                offset_x + (TAILLE_PLATEAU-2) * CASE_TAILLE,
                offset_y + i * CASE_TAILLE,
                CASE_TAILLE,
                CASE_TAILLE
            };
			int est_rouge_droite = SDL_PointInRect(&(SDL_Point){mouse_x, mouse_y}, &droite);
			SDL_Texture* texDroite = SDL_PointInRect(&(SDL_Point){mouse_x, mouse_y}, &droite) ? flecheTextureRouge : flecheTexture;
            SDL_RenderCopyEx(renderer, texDroite, NULL, &droite, 180, NULL, SDL_FLIP_NONE);
            boutons[index++] = (BoutonFleche){droite, numero + 3, 1,est_rouge_droite};
        }

    }
    SDL_RenderPresent(renderer);
    
}

void afficher_labyrintheSDL(int n, int labyrinthe[TAILLE_PLATEAU][TAILLE_PLATEAU], SDL_Renderer* renderer, SDL_Window* window, int mouse_x, int mouse_y) {
    if (n < 2) {
        printf("La taille du labyrinthe doit être au moins 2.\n");
        return;
    }

    // Récupère la taille de la fenêtre
    int w, h;
    SDL_GetWindowSize(window, &w, &h);

    // Calcule la taille du plateau
    int plateau_w = n * CASE_TAILLE;
    int plateau_h = n * CASE_TAILLE;

    // Coordonnées pour centrer le plateau
    int offset_x = (w - plateau_w) / 5;
    int offset_y = (h - plateau_h) / 2;

    // Création de la flèche
    SDL_Surface* flecheSurface = IMG_Load("SDL/images/Fleche.png");
    SDL_Surface* flecheRougeSurface = IMG_Load("SDL/images/fleche_rouge.png");
    SDL_Surface* joueurRougeSurface = IMG_Load("SDL/images/pion_rouge.png");
    SDL_Surface* joueurBleuSurface = IMG_Load("SDL/images/pion_bleu.png");
    SDL_Surface* joueurVertSurface = IMG_Load("SDL/images/pion_vert.png");
    SDL_Surface* joueurBlancSurface = IMG_Load("SDL/images/pion_blanc.png");
    SDL_Surface* tresorSurface = IMG_Load("SDL/images/tresor.png");
    SDL_Surface* murSurface = IMG_Load("SDL/images/mur.png");
    SDL_Surface* cheminSurface = IMG_Load("SDL/images/chemin.png");

    if (!flecheSurface || !flecheRougeSurface || !joueurRougeSurface || !joueurVertSurface || !joueurBleuSurface || !joueurBlancSurface || !murSurface || !cheminSurface) {
        printf("Erreur chargement des images: %s\n", IMG_GetError());
        return;
    }

    SDL_Texture* flecheTexture = SDL_CreateTextureFromSurface(renderer, flecheSurface);
    SDL_Texture* flecheTextureRouge = SDL_CreateTextureFromSurface(renderer, flecheRougeSurface);
    SDL_Texture* joueurTextureRouge = SDL_CreateTextureFromSurface(renderer, joueurRougeSurface);
    SDL_Texture* joueurTextureBleu = SDL_CreateTextureFromSurface(renderer, joueurBleuSurface);
    SDL_Texture* joueurTextureBlanc = SDL_CreateTextureFromSurface(renderer, joueurBlancSurface);
    SDL_Texture* joueurTextureVert = SDL_CreateTextureFromSurface(renderer, joueurVertSurface);
    SDL_Texture* tresorTexture = SDL_CreateTextureFromSurface(renderer, tresorSurface);
    SDL_Texture* murTexture = SDL_CreateTextureFromSurface(renderer, murSurface);
    SDL_Texture* cheminTexture = SDL_CreateTextureFromSurface(renderer, cheminSurface);

    SDL_FreeSurface(flecheSurface);
    SDL_FreeSurface(flecheRougeSurface);
    SDL_FreeSurface(joueurRougeSurface);
    SDL_FreeSurface(joueurVertSurface);
    SDL_FreeSurface(joueurBleuSurface);
    SDL_FreeSurface(joueurBlancSurface);
    SDL_FreeSurface(tresorSurface);
    SDL_FreeSurface(murSurface);
    SDL_FreeSurface(cheminSurface);

    if (!flecheTexture || !flecheTextureRouge || !joueurTextureVert || !joueurTextureRouge || !joueurTextureBleu || !joueurTextureBlanc || !cheminTexture || !murTexture) {
        printf("Erreur création des textures: %s\n", SDL_GetError());
        return;
    }


    // Affichage des cases (coeur du labyrinthe)
    for (int i = 0; i < TAILLE_PLATEAU; i++) {
        for (int j = 0; j < TAILLE_PLATEAU; j++) {
            SDL_Rect case_plateau = {
                offset_x + j * CASE_TAILLE,
                offset_y + i * CASE_TAILLE,
                CASE_TAILLE,
                CASE_TAILLE
            };

            switch (labyrinthe[i][j]) {
                case 0: SDL_RenderCopy(renderer, murTexture, NULL, &case_plateau); break;           // Mur
                case 1: SDL_RenderCopy(renderer, cheminTexture, NULL, &case_plateau); break;        //Chemin
                case 2: SDL_RenderCopy(renderer, joueurTextureRouge, NULL, &case_plateau);break;   //Joueur 1                                                                                  // Joueur 1
                case 3: SDL_RenderCopy(renderer, joueurTextureVert, NULL, &case_plateau);break;    // Joueur 2
                case 4: SDL_RenderCopy(renderer, joueurTextureBleu, NULL, &case_plateau);break;          // Joueur 3
                case 5: SDL_RenderCopy(renderer, joueurTextureBlanc, NULL, &case_plateau);break;       // Joueur 4
                case 6: SDL_RenderCopy(renderer, tresorTexture, NULL, &case_plateau);break;       // Trésor
            }

            if(i==0 || j==0 || i==n-1 || j==n-1){
                SDL_SetRenderDrawColor(renderer, 172, 115, 57, 255);
                SDL_RenderFillRect(renderer, &case_plateau);
            }            
        }
    }
    BoutonFleche boutons[NB_BOUTONS];
    afficher_fleches_et_initialiser_boutons(renderer,flecheTexture,flecheTextureRouge, boutons, mouse_x, mouse_y);
    SDL_DestroyTexture(flecheTexture);
    SDL_DestroyTexture(flecheTextureRouge);
    SDL_DestroyTexture(joueurTextureRouge);
    SDL_DestroyTexture(joueurTextureBleu);
    SDL_DestroyTexture(joueurTextureVert);
    SDL_DestroyTexture(joueurTextureBlanc);
    SDL_DestroyTexture(tresorTexture);
    SDL_DestroyTexture(murTexture);
    SDL_DestroyTexture(cheminTexture);

}

void affichage_background(SDL_Renderer* renderer, SDL_Window* window){
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);

    // Récupère la taille de la fenêtre
    int w, h;
    SDL_GetWindowSize(window, &w, &h);

    // Fond marron
    SDL_SetRenderDrawColor(renderer, 172, 115, 57, 255); 
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);// transparence des couleurs

    // Fond marron clair pour les instructions sur le côté
    SDL_Rect zone_texte = {w-w/3, 0, w-w/2.8, h};
    SDL_SetRenderDrawColor(renderer, 210, 166, 121, 255);
    SDL_RenderFillRect(renderer, &zone_texte);
}

bool caseCliquee(int n, SDL_Window* window, int mouse_x, int mouse_y, int* ligne, int* colonne) {
    int w, h;
    SDL_GetWindowSize(window, &w, &h);

    int plateau_w = n * CASE_TAILLE;
    int plateau_h = n * CASE_TAILLE;

    int offset_x = (w - plateau_w) / 5;
    int offset_y = (h - plateau_h) / 2;

    if (mouse_x < offset_x || mouse_y < offset_y ||
        mouse_x >= offset_x + plateau_w || mouse_y >= offset_y + plateau_h) {
        return false; // Hors du plateau
    }

    *colonne = (mouse_x - offset_x) / CASE_TAILLE;
    *ligne   = (mouse_y - offset_y) / CASE_TAILLE;

    // Vérifie que c’est bien dans la grille
    if (*ligne >= 0 && *ligne < n-1 && *colonne >= 0 && *colonne < n-1) {
        return true;
    }

    return false;
}

void initialiser_boutons_fleches(SDL_Window* window, BoutonFleche* boutons) {
    int w, h;
    SDL_GetWindowSize(window, &w, &h);

    int offset_x = (w - (TAILLE_PLATEAU-2) * CASE_TAILLE) / 2;
    int offset_y = (h - (TAILLE_PLATEAU-2) * CASE_TAILLE) / 2;

    int index = 0;
    for (int i = 0; i < TAILLE_PLATEAU-1; i++) {
        if (i % 2 != 0) {
            int numero = (i / 2) + 1;

            // Flèche en haut (descend) - sens 0
            SDL_Rect haut = {
                offset_x + i * CASE_TAILLE,
                offset_y - CASE_TAILLE,
                CASE_TAILLE,
                CASE_TAILLE
            };
            boutons[index++] = (BoutonFleche){haut, numero, 0};

            // Flèche en bas (monte) - sens 1
            SDL_Rect bas = {
                offset_x + i * CASE_TAILLE,
                offset_y + (TAILLE_PLATEAU-2) * CASE_TAILLE,
                CASE_TAILLE,
                CASE_TAILLE
            };
            boutons[index++] = (BoutonFleche){bas, numero, 1};

            // Flèche à gauche (vers la droite) - sens 0
            SDL_Rect gauche = {
                offset_x - CASE_TAILLE,
                offset_y + i * CASE_TAILLE,
                CASE_TAILLE,
                CASE_TAILLE
            };
            boutons[index++] = (BoutonFleche){gauche, numero + 3, 0};

            // Flèche à droite (vers la gauche) - sens 1
            SDL_Rect droite = {
                offset_x + (TAILLE_PLATEAU-2) * CASE_TAILLE,
                offset_y + i * CASE_TAILLE,
                CASE_TAILLE,
                CASE_TAILLE
            };
            boutons[index++] = (BoutonFleche){droite, numero + 3, 1};
        }
    }
}


