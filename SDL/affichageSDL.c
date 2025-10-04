#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "affichageSDL.h"

int init(SDL_Window** window, SDL_Renderer** renderer, const char* titre, int w, int h, SDL_Texture** background, TTF_Font** font) {
    SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    // création de la fenêtre
    *window = SDL_CreateWindow(titre, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);
    if (*window == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[ERROR] > %s", SDL_GetError());
        SDL_Quit();
        TTF_Quit();
        return EXIT_FAILURE;
    }

    // création du render
    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (*renderer == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_RENDER, "[ERROR] > %s", SDL_GetError());
        SDL_Quit();
        TTF_Quit();
        return EXIT_FAILURE;
    }

    SDL_Surface* imgfond = IMG_Load("SDL/images/lab.png");
    *background = SDL_CreateTextureFromSurface(*renderer, imgfond);
    SDL_FreeSurface(imgfond);

    if (TTF_Init() == -1) {
        printf("Erreur TTF: %s\n", TTF_GetError());
        return -1;
    }

    *font = chargerPolice("SDL/police.ttf", 40);
    if (!font) {
        fprintf(stderr, "Erreur : police non chargée !\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

TTF_Font* chargerPolice(const char* chemin, int taille) {
    TTF_Font* font = TTF_OpenFont(chemin, taille);
    if (!font) {
        fprintf(stderr, "Erreur chargement police '%s' : %s\n", chemin, TTF_GetError());
        return NULL;
    }
    return font;
}

int bouton(int x, int y, SDL_Rect bouton) {
    return x >= bouton.x && x <= bouton.x + bouton.w && y >= bouton.y && y <= bouton.y + bouton.h;
}

void freeSDL(SDL_Renderer*renderer, SDL_Window* window, SDL_Texture* texture, TTF_Font* font, Mix_Chunk* musique){
    if (renderer){
        SDL_DestroyRenderer(renderer);
    }
    if (window){
        SDL_DestroyWindow(window);
    }
    if (texture){
        SDL_DestroyTexture(texture);
    }
    if (musique){
        Mix_FreeChunk(musique);
        Mix_CloseAudio();
    }
    if (font){
        TTF_CloseFont(font);
    }
    IMG_Quit();
    SDL_Quit();
}

void animationVictoire(SDL_Renderer *renderer, SDL_Window *window, Joueur *joueurs, int tour_du_joueur) {
    int w, h;
    SDL_GetWindowSize(window, &w, &h);

    bool fini = false;
    SDL_Event event;
    Uint32 last_flash_time = SDL_GetTicks();
    bool visible = true;

    TTF_Font *titre = chargerPolice("SDL/police.ttf", 48);
    TTF_Font *normal = chargerPolice("SDL/police.ttf", 24);
    SDL_Color rouge = {255, 0, 0, 255};
    SDL_Color blanc = {255, 255, 255, 255};

    char message[100];
    sprintf(message, "Bravo %s, vous avez gagne !", joueurs[tour_du_joueur].username);

    Uint32 start_time = SDL_GetTicks();
    Uint32 tmax = 15000; // durée max avant timeout automatique (15s)

    while (!fini && SDL_GetTicks() - start_time < tmax) {
        // Gestion des événements
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                fini = true;
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
                fini = true;
        }

        // Effet clignotement
        if (SDL_GetTicks() - last_flash_time > 500) {
            visible = !visible;
            last_flash_time = SDL_GetTicks();
        }

        // Nettoyage de l'écran
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // fond noir
        SDL_RenderClear(renderer);

        // Feux d'artifice simples
        for (int i = 0; i < 20; i++) {
            SDL_SetRenderDrawColor(renderer, rand() % 255, rand() % 255, rand() % 255, 255);
            int cx = rand() % w;
            int cy = rand() % h;
            for (int j = 0; j < 10; j++) {
                int dx = rand() % 40 - 20;
                int dy = rand() % 40 - 20;
                SDL_RenderDrawLine(renderer, cx, cy, cx + dx, cy + dy);
            }
        }

        // Texte principal qui clignote
        if (visible)
            affichertexte(renderer, message, w/3, h/1.5, titre, rouge);

        // Texte secondaire
        affichertexte(renderer, "Appuyez sur ENTREE pour une nouvelle partie", w/3.5, h-80, normal, blanc);

        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }

    TTF_CloseFont(titre);
    TTF_CloseFont(normal);
}

