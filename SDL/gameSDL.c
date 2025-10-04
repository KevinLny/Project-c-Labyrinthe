#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <time.h>

#include "gameSDL.h"

GameState gameSDL(SDL_Renderer *renderer, SDL_Window *window, int labyrinthe[TAILLE_PLATEAU][TAILLE_PLATEAU], Joueur *joueur, int nb_joueur, int nb_tresors)
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        fprintf(stderr, "Erreur Mix_OpenAudio : %s\n", Mix_GetError());
        return QUIT;
    }

    Mix_Chunk* mvt = Mix_LoadWAV("SDL/sound/move-self.wav");
    Mix_Chunk* tresor = Mix_LoadWAV("SDL/sound/game-win.wav");
    Mix_Chunk* illegal = Mix_LoadWAV("SDL/sound/illegal.wav");
    Mix_Chunk* son_tuile = Mix_LoadWAV("SDL/sound/click.wav");

    if (!mvt) {
        fprintf(stderr, "Erreur mvt Mix_LoadWAV : %s\n", Mix_GetError());
    }
    if (!tresor) {
        fprintf(stderr, "Erreur tresor Mix_LoadWAV : %s\n", Mix_GetError());
    }
    if (!illegal) {
        fprintf(stderr, "Erreur illegal Mix_LoadWAV : %s\n", Mix_GetError());
    }

    int tour_du_joueur = 0;
    bool en_jeu = true;

    BoutonFleche boutons[NB_BOUTONS];
    initialiser_boutons_fleches(window,boutons);

    SDL_Surface* flecheSurface = IMG_Load("SDL/images/Fleche.png");
    SDL_Surface* flecheRougeSurface = IMG_Load("SDL/images/fleche_rouge.png");

    if (!flecheSurface || !flecheRougeSurface) {
        fprintf(stderr, "Erreur IMG_Load : %s\n", IMG_GetError());
        return QUIT;
    }

    SDL_Texture* flecheTexture = SDL_CreateTextureFromSurface(renderer, flecheSurface);
    SDL_Texture* flecheTextureRouge = SDL_CreateTextureFromSurface(renderer, flecheRougeSurface);

    // Libération des surfaces après création des textures
    SDL_FreeSurface(flecheSurface);
    SDL_FreeSurface(flecheRougeSurface);

    if (!flecheTexture || !flecheTextureRouge) {
        fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s\n", SDL_GetError());
        return QUIT;
    }
    
    TTF_Font * titre = chargerPolice("SDL/police.ttf", 34);
    TTF_Font* normal = chargerPolice("SDL/police.ttf", 34);
    SDL_Color noir = { 0, 0, 0, 255 };

    srand(time(NULL));

    int w, h;
    SDL_GetWindowSize(window, &w, &h);

    //début du jeu
    while (en_jeu)
    {
        bool a_deplace = false;
        bool a_place_tuile = false;
        bool tour_termine = false;
        bool msg_maj = false;

        int ancienne_case = -1;

        char msg[100] = "";

        SDL_Event event;

        //début du tour du joueur
        while (!tour_termine)
        {   
            // détection des cases avec la souris
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);

            // Actualisation de l'écran
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderClear(renderer);

            affichage_background(renderer, window);
            txt_init_tour(renderer, nb_joueur, nb_tresors, joueur, tour_du_joueur, w, h);
            afficher_labyrintheSDL(TAILLE_PLATEAU, labyrinthe, renderer, window, mouseX, mouseY);
			afficher_fleches_et_initialiser_boutons(renderer, flecheTexture, flecheTextureRouge, boutons, mouseX, mouseY);

            if (msg_maj) {
                affichertexte(renderer, msg, w - w / 3.6, h / 3, titre, noir);
            }

            SDL_RenderPresent(renderer);

            while (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                case SDL_QUIT:
                    tour_termine = true;
                    SDL_DestroyTexture(flecheTexture);
                    SDL_DestroyTexture(flecheTextureRouge);
                    Mix_FreeChunk(mvt);
                    Mix_FreeChunk(tresor);
                    Mix_FreeChunk(illegal);
                    Mix_FreeChunk(son_tuile);
                    return QUIT;
                    break;

                    case SDL_MOUSEBUTTONDOWN: 
                        if (event.button.button == SDL_BUTTON_LEFT) {

                            int cibleX = joueur[tour_du_joueur].x;
                            int cibleY = joueur[tour_du_joueur].y;

                            if (caseCliquee(TAILLE_PLATEAU, window, event.button.x, event.button.y, &cibleX, &cibleY)){
                                ancienne_case = labyrinthe[cibleX][cibleY];

                                //si le joueur a obtenus tous ses trésors, il ne peut plus aller sur les cases trésors
                                if (ancienne_case == 6 && joueur[tour_du_joueur].nbTresors >= nb_tresors)
                                {
                                    snprintf(msg, sizeof(msg), "Vous avez deja tous vos tresors");
                                    Mix_PlayChannel(-1, illegal, 0);
                                    msg_maj = true;
                                    break;
                                }
                                if (!a_deplace && est_cheminLee(labyrinthe, joueur[tour_du_joueur], cibleX, cibleY) > 0)
                                {
                                   
                                    int ancienX = joueur[tour_du_joueur].x;
                                    int ancienY = joueur[tour_du_joueur].y;
                                    labyrinthe[ancienX][ancienY] = 1;

                                    // déplace le joueur après un clic de souris
                                    deplacerJoueur(joueur, tour_du_joueur, labyrinthe, cibleX, cibleY);
                                
                                    // Ajoute le pion sur sa nouvelle position
                                    labyrinthe[cibleX][cibleY] = 2 + tour_du_joueur;
                                    snprintf(msg, sizeof(msg), "Case cliquee : (%d ; %d)", cibleX, cibleY);
                                    a_deplace = true;
                                    msg_maj = true;

                                    

                                    //le joueur a cliqué sur une case trésor
                                    if (ancienne_case == 6 && joueur[tour_du_joueur].nbTresors < nb_tresors )
                                    {
                                        joueurSurTresor(joueur, tour_du_joueur, labyrinthe);
                                        Mix_PlayChannel(-1, tresor, 0);
                                        labyrinthe[cibleX][cibleY] = 2 + tour_du_joueur;
                                        snprintf(msg, sizeof(msg), "%s a trouve un tresor !", joueur[tour_du_joueur].username);
                                        msg_maj = true;
                                        tour_termine = true;
                                    } else {
                                        Mix_PlayChannel(-1, mvt, 0);
                                    }
                                } else {
                                    Mix_PlayChannel(-1, illegal, 0);
                                }
                            }
                        if (!a_place_tuile) {
                            for (int i = 0; i < NB_BOUTONS; i++) {
								    srand(time(NULL));
    								int tuile = rand() % 2;

                                if (boutons[i].est_rouge) {
                                    switch (boutons[i].numero) {
                                        case 1:
                                            if (boutons[i].sens == 1)
                                                glisser_tuile(boutons[i].numero, boutons[i].sens, tuile, labyrinthe, joueur, nb_joueur);
                                            else
                                                glisser_tuile(boutons[i].numero, boutons[i].sens, tuile, labyrinthe, joueur, nb_joueur);
                                            a_place_tuile = true;
                                            break;

                                        case 2:
                                            if (boutons[i].sens == 1)
                                                glisser_tuile(boutons[i].numero, boutons[i].sens, tuile, labyrinthe, joueur, nb_joueur);
                                            else
                                                glisser_tuile(boutons[i].numero, boutons[i].sens, tuile, labyrinthe, joueur, nb_joueur);
                                            a_place_tuile = true;
                                            break;

                                        case 3:
                                            if (boutons[i].sens == 1)
                                                glisser_tuile(boutons[i].numero, boutons[i].sens, tuile, labyrinthe, joueur, nb_joueur);
                                            else
                                                glisser_tuile(boutons[i].numero, boutons[i].sens, tuile, labyrinthe, joueur, nb_joueur);
                                            a_place_tuile = true;
                                            break;

                                        case 4:
                                            if (boutons[i].sens == 1)
                                                glisser_tuile(boutons[i].numero, boutons[i].sens, tuile, labyrinthe, joueur, nb_joueur);
                                            else
                                                glisser_tuile(boutons[i].numero, boutons[i].sens, tuile, labyrinthe, joueur, nb_joueur);
                                            a_place_tuile = true;
                                            break;

                                        case 5:
                                            if (boutons[i].sens == 1)
                                                glisser_tuile(boutons[i].numero, boutons[i].sens, tuile, labyrinthe, joueur, nb_joueur);
                                            else
                                                glisser_tuile(boutons[i].numero, boutons[i].sens, tuile, labyrinthe, joueur, nb_joueur);
                                            a_place_tuile = true;
                                            break;

                                        case 6:
                                            if (boutons[i].sens == 1)
                                                glisser_tuile(boutons[i].numero, boutons[i].sens, tuile, labyrinthe, joueur, nb_joueur);
                                            else
                                                glisser_tuile(boutons[i].numero, boutons[i].sens, tuile, labyrinthe, joueur, nb_joueur);
                                            a_place_tuile = true;
                                            break;
                                    }
                                }
                            }
                        }
                        if (a_place_tuile){
                            Mix_PlayChannel(-1, son_tuile, 0);
                        }                       
                    }
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_RETURN:
                        tour_termine = true;
                        tour_du_joueur = (tour_du_joueur + 1) % nb_joueur;
                        break;

                    case SDLK_h:
                        SDL_RenderClear(renderer);
                        affichage_background(renderer, window);
                        afficher_labyrintheSDL(TAILLE_PLATEAU, labyrinthe, renderer, window, mouseX, mouseY);
                        affichage_help(renderer, window);
                        SDL_RenderPresent(renderer);
                        SDL_Delay(10000);
                        break;

                    case SDLK_q:
                        printf("Quitter le jeu\n");
                        Mix_FreeChunk(mvt);
                        Mix_FreeChunk(tresor);
                        Mix_FreeChunk(illegal);
                        Mix_FreeChunk(son_tuile);
                        SDL_DestroyTexture(flecheTexture);
                        SDL_DestroyTexture(flecheTextureRouge);
                        return QUIT;
                    
                    case SDLK_ESCAPE:
                        SDL_DestroyTexture(flecheTexture);
                        SDL_DestroyTexture(flecheTextureRouge);
                        Mix_FreeChunk(mvt);
                        Mix_FreeChunk(tresor);
                        Mix_FreeChunk(illegal);
                        Mix_FreeChunk(son_tuile);
                        printf("retour au menu\n");
                        SDL_SetWindowFullscreen(window, 0);
                        return MENU;
                    }
                    break;
                }
            }
            SDL_Delay(10);
            if (winner(joueur, nb_joueur, nb_tresors)){
                animationVictoire(renderer, window, joueur, tour_du_joueur);
                tour_termine = true;
                en_jeu = false;
                Mix_FreeChunk(tresor);
                Mix_FreeChunk(illegal);
                Mix_CloseAudio();
                TTF_CloseFont(normal);
                SDL_DestroyTexture(flecheTexture);
                SDL_DestroyTexture(flecheTextureRouge);
                return INIT_LABYRINTHE;                 
            }
        }
    }
    return INIT_LABYRINTHE; 
}

GameState lancerLabyrinthe(SDL_Renderer *renderer, SDL_Window *window, Joueur *joueurs, int nb_joueurs, int labyrinthe[TAILLE_PLATEAU][TAILLE_PLATEAU], int nb_tresors){

    init_plateau(TAILLE_PLATEAU, labyrinthe);
    initJoueurs(nb_joueurs, joueurs, labyrinthe);
    placer_tresors(labyrinthe, nb_tresors);

    int largeur = 0, hauteur = 0;
    SDL_GetWindowSize(window, &largeur, &hauteur);
    SDL_Rect rectangleFond = { 0, 0, largeur, hauteur };

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, NULL, NULL, &rectangleFond);
        
    affichage_background(renderer, window);
    affichage_regles(renderer, window);

    bool attente = true;
    SDL_Event e;

    while (attente)
    {
        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
                case SDL_QUIT:
                    return QUIT;

                case SDL_KEYDOWN:
                    switch (e.key.keysym.sym)
                    {
                        case SDLK_SPACE:
                            return INIT_LABYRINTHE;

                        case SDLK_RETURN:
                            attente = false;
                            break;

                        case SDLK_q:
                            return QUIT;

                        case SDLK_ESCAPE:
                            SDL_SetWindowFullscreen(window, 0);
                            return MENU;
                    }
                    break;
            }
        }
        
        int mouseX = 0, mouseY = 0;
        SDL_GetMouseState(&mouseX, &mouseY);
        afficher_labyrintheSDL(TAILLE_PLATEAU, labyrinthe, renderer, window,mouseX, mouseY );

        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }
    return JEU;
}

GameState boucleMenu(SDL_Renderer *pRenderer, SDL_Window *window, Joueur joueurs[], SDL_Texture* background, TTF_Font* font, int* nb_joueurs, int* nb_tresors){

    //affichage dynamique de la fenêtre
    int hauteur;
    int largeur;

    SDL_GetWindowSize(window, &largeur, &hauteur);
    SDL_Rect rectangle = { 0, 0, largeur, hauteur };

    // définition des couleurs
    SDL_Color Black = { 0, 0, 0, 255 };
    SDL_Color Red = { 255, 0, 0, 255 };

    SDL_Rect boutonSolo = {450, 300, 135, 50}; // zone du bouton "JOUER"
	SDL_Rect boutonMulti = {440, 400, 135, 50};
    SDL_Rect boutonQuitter = {430, 500, 180, 50};
    SDL_Rect bouton2J = {440, 250, 180, 50};
    SDL_Rect bouton3J = {300, 350, 210, 50};
    SDL_Rect bouton4J = {600, 350, 210, 50};
	SDL_Rect retour = {470,500,210,50};
    SDL_Rect bouton1T = {300, 250, 180, 50};
    SDL_Rect bouton2T = {600, 250, 180, 50};
    SDL_Rect bouton3T = {300, 350, 210, 50};
    SDL_Rect bouton4T = {600, 350, 210, 50};

    SDL_Color boutonColorSolo = Black;
	SDL_Color boutonColorMulti = Black;
    SDL_Color boutonC2J = Black;
    SDL_Color boutonC3J = Black;
    SDL_Color boutonC4J = Black;
	SDL_Color boutonretour = Black;
    SDL_Color boutonColorQuitter = Black;
    SDL_Color boutonC1T = Black;
    SDL_Color boutonC2T = Black;
    SDL_Color boutonC3T = Black;
    SDL_Color boutonC4T = Black;

    // boucle principale
    SDL_Event event;
    int run = 1;
    int ouverture = 1;
    int menu1 = 0;
	int menu2 = 0;
    int menu3 = 0;
	int joueur_courant = 0;

    strcpy(joueurs[0].username, "");
    strcpy(joueurs[1].username, "");
    strcpy(joueurs[2].username, "");
    strcpy(joueurs[3].username, "");
    
    while (run) {
        while(SDL_PollEvent(&event)){
            switch (event.type) {
                case SDL_QUIT:
                    printf("QUITTER\n");
                    return QUIT;
                    break;

                case SDL_KEYDOWN:
                    if (menu3) {
                        //effacer un caractère du pseudo
                        if (event.key.keysym.sym == SDLK_BACKSPACE) {
                            size_t len = strlen(joueurs[joueur_courant].username);
                            if (len > 0) {
                                joueurs[joueur_courant].username[len - 1] = '\0';
                            }
                        }
                        // Entrée : passer au pseudo suivant
                        else if (event.key.keysym.sym == SDLK_RETURN) {
                            if (joueur_courant < *nb_joueurs - 1) {
                                // On passe au prochain joueur
                                joueur_courant++;
                            } else {
                                // On quitte la saisie après avoir rempli tous les pseudos
                                menu3 = 0;
                                SDL_StopTextInput();
                                return INIT_LABYRINTHE;
                            }
                        }
                    }else{
                        //quitter le jeu
                        switch (event.key.keysym.sym) {
                            case SDLK_q:
                                run = 0;
                                return QUIT;
                                break;
                        }
                    }
                    break;
                case SDL_TEXTINPUT:                   //on stock le pseudo
                    if (menu3 && joueur_courant < *nb_joueurs) {
                        if (strlen(joueurs[joueur_courant].username) < MAX_USERNAME - 1) {
                            strcat(joueurs[joueur_courant].username, event.text.text);
                        }
                    }
                    if (menu3 && event.key.keysym.sym == SDLK_BACKSPACE) {
                        size_t len = strlen(joueurs[joueur_courant].username);
                        if (len > 0) {
                            joueurs[joueur_courant].username[len - 1] = '\0';
                        }
                    }
                break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        int x = event.button.x;
                        int y = event.button.y;

                        // Vérification du clic sur le bouton "JOUER"
                        if (bouton(x,y,boutonSolo)&& ouverture==1) {
                            printf("Bouton SOLO cliqué !\n");
                            ouverture = 0;
                            menu2 = 1;
                            *nb_joueurs =1;
                            break;
                        }
                        if (bouton(x,y,boutonMulti)&& ouverture==1) {
                            printf("Bouton MULTI cliqué !\n");
                            ouverture = 0;
                            menu1 = 1;
                            break;
                        }
                        // Vérification du clic sur le bouton "QUITTER"
                        if (bouton(x,y,boutonQuitter) && ouverture == 1 && menu1 == 0 && menu2 == 0 && menu3 == 0) {
                            printf("Bouton QUITTER cliqué !\n");
                            return QUIT;
                            break;
                        }
                        if (bouton(x,y,retour)) {
                            if (menu1 ==1) {
                                menu1 = 0;
                                ouverture = 1;
                            }
                            if (menu2 ==1) {
                                menu2 = 0;
                                menu1 =0;
                                ouverture = 1;
                            }
                            break;
                        }
                        if ((bouton(x,y,bouton2J) && menu1 ==1 )|| (bouton(x,y,bouton3J) && menu1 ==1) || (bouton(x,y,bouton4J) && menu1 ==1)) {
                            if (bouton(x,y,bouton2J)){
                                *nb_joueurs = 2;
                            }
                            if (bouton(x,y,bouton3J)){
                                *nb_joueurs = 3;
                            }
                            if (bouton(x,y,bouton4J)){
                                *nb_joueurs = 4;
                            }
                            menu1 = 0;
                            ouverture = 0;
                            menu2 = 1;
                            break;
                        }
                        if ((bouton(x,y,bouton1T) && menu2 ==1)||
                            (bouton(x,y,bouton2T) && menu2 ==1) ||
                            (bouton(x,y,bouton3T) && menu2 ==1) ||
                            (bouton(x,y,bouton4T) && menu2 ==1))
                        {
                            if (bouton(x,y,bouton1T)){
                                *nb_tresors = 1;
                                }
                            if (bouton(x,y,bouton2T)){
                                *nb_tresors = 2;
                                }
                            if (bouton(x,y,bouton3T)){
                                *nb_tresors = 3;
                                }
                            if (bouton(x,y,bouton4T)){
                                *nb_tresors = 4;
                                }
                                menu1 = 0;
                                ouverture = 0;
                                menu2 = 0;
                                menu3=1;
                                SDL_StartTextInput();
                                break;
                        }

                    }
                break;
            }
        }

        // Changements des couleurs au passage de la souris
        boutonColorSolo = Black;
		boutonColorMulti = Black;
        boutonColorQuitter = Black;
        boutonC2J = Black;
        boutonC3J = Black;
        boutonC4J = Black;
        boutonretour = Black;
        boutonC1T = Black;
        boutonC2T = Black;
        boutonC3T = Black;
        boutonC4T = Black;

        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        if (bouton(mouseX, mouseY, boutonSolo)) {
            boutonColorSolo = Red;
        }
  		if (bouton(mouseX, mouseY, boutonMulti)) {
            boutonColorMulti = Red;
        }
        if (bouton(mouseX, mouseY, bouton2J)) {
            boutonC2J = Red;
        }
        if (bouton(mouseX, mouseY, bouton3J)) {
            boutonC3J = Red;
        }
        if (bouton(mouseX, mouseY, bouton4J)) {
            boutonC4J = Red;
        }
        if (bouton(mouseX, mouseY, retour)) {
            boutonretour = Red;
        }
        if (bouton(mouseX, mouseY, boutonQuitter)) {
            boutonColorQuitter = Red;
        }
        if (bouton(mouseX, mouseY, bouton1T)) {
            boutonC1T = Red;
        }
        if (bouton(mouseX, mouseY, bouton2T)) {
            boutonC2T = Red;
        }
        if (bouton(mouseX, mouseY, bouton3T)) {
            boutonC3T = Red;
        }
        if (bouton(mouseX, mouseY, bouton4T)) {
            boutonC4T = Red;
        }

        SDL_RenderClear(pRenderer);     // Efface l'écran à chaque boucle
        SDL_RenderCopy(pRenderer, background, NULL, &rectangle); // Copie de l'image de fond dans le rectangle

        // Affichage des textes et du bouton avec la couleur dynamique
        if (ouverture){
            affichertexte(pRenderer, "BIENVENUE DANS LE JEU : ", 270, 150, font, Black);
            affichertexte(pRenderer, "SOLO", 450, 300, font, boutonColorSolo);
			affichertexte(pRenderer, "MULTI", 440, 400, font, boutonColorMulti);
            affichertexte(pRenderer, "QUITTER", 430, 500, font, boutonColorQuitter);
        }

        if (menu1){
            affichertexte(pRenderer, "2 JOUEURS ", 440, 250, font, boutonC2J);
            affichertexte(pRenderer, "3 JOUEURS ", 300, 350, font, boutonC3J);
            affichertexte(pRenderer, "4 JOUEURS ", 600, 350, font, boutonC4J);
            affichertexte(pRenderer, "RETOUR", 470, 500, font, boutonretour);
        }
        if (menu2){
            affichertexte(pRenderer, "1 TRESOR ", 300, 250, font, boutonC1T);
            affichertexte(pRenderer, "2 TRESORS ", 600, 250, font, boutonC2T);
            affichertexte(pRenderer, "3 TRESORS ", 300, 350, font, boutonC3T);
            affichertexte(pRenderer, "4 TRESORS ", 600, 350, font, boutonC4T);
            affichertexte(pRenderer, "RETOUR", 470, 500, font, boutonretour);
        }
        if (menu3){
            affichertexte(pRenderer, "ENTREZ VOS PSEUDOS :", 320, 50, font, Black);
    			for (int i = 0; i < *nb_joueurs; i++) {
        			SDL_Rect pseudoRect = {400, 150 + (i * 80), 300, 70};
        			SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
        			SDL_RenderDrawRect(pRenderer, &pseudoRect);
        			affichertexte(pRenderer, joueurs[i].username, pseudoRect.x + 5, pseudoRect.y + 5, font, Black);
        			if (i == joueur_courant) {
            			SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 255);
            			SDL_RenderDrawRect(pRenderer, &pseudoRect); // surligner l'actif
                    }
                }
        }

        SDL_RenderPresent(pRenderer); // Présente le rendu
        SDL_Delay(16);
    }
    return QUIT;
}