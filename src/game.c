#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../include/utils.h"
#include "../include/affichage.h"
#include "../include/plateau.h"
#include "../include/joueur.h"
  

CommandeAnalyse analyser_commande(const char *input) {
    CommandeAnalyse result = {CMD_UNKNOWN, -1, -1, -1};
    char cmd[10];
    int arg1, arg2, arg3;

    int count = sscanf(input, "%s %d %d %d", cmd, &arg1, &arg2, &arg3);

    if (strcasecmp(cmd, "help") == 0) result.type = CMD_HELP;
    else if (strcasecmp(cmd, "regles") == 0) result.type = CMD_REGLE;
    else if (strcasecmp(cmd, "liste") == 0) result.type = CMD_LISTE;
    else if (strcasecmp(cmd, "scores") == 0) result.type = CMD_SCORE;
    else if (strcasecmp(cmd, "show") == 0) result.type = CMD_SHOW;
    else if (strcasecmp(cmd, "next") == 0) result.type = CMD_NEXT;
    else if (strcasecmp(cmd, "quit") == 0) result.type = CMD_QUIT;
    else if (strcasecmp(cmd, "move") == 0 && count >= 3) {
        result.type = CMD_MOVE;
        result.arg1 = arg1;
        result.arg2 = arg2;
    }
    else if (strcasecmp(cmd, "place") == 0 && count == 4) {
        result.type = CMD_PLACE;
        result.arg1 = arg1;
        result.arg2 = arg2;
        result.arg3 = arg3;
    }

    return result;
}

void afficher_regles() {
    printf("\n📜 Commandes disponibles :\n");
    printf("  move x y         - Se déplacer vers la case (x, y)\n");
    printf("  place x y d      - sur le plateau il y a des chiffres de 1 à 6 c'est x .Sens = 0 gauche/haut sens = 1 droite/bas pour y. Tuile = 0 pour un mur et tuile = 1 pour un chemin avec d\n");
    printf("  next             - Fin de tour");
    printf("  score            - Afficher les scores\n");
    printf("  show             - Affiche le labyrinthe\n");
    printf("  help             - Afficher les règles du jeu\n");
    printf("  quit             - Terminer la partie\n\n");
}

bool winner(Joueur* joueurs, int nb_joueur, int nb_tresors) {
    for (int i = 0; i < nb_joueur; i++) {
        if (joueurs[i].x == joueurs[i].x_init &&
            joueurs[i].y == joueurs[i].y_init &&
            joueurs[i].nbTresors == nb_tresors) {
            printf("✅ Joueur %s a gagné !\n", joueurs[i].username);
            return true;
        }
    }
    return false;
}

int demander_nombre_joueurs() {
    int nb_joueur = 0;
    do {
        printf("Entrez le nombre de joueurs (1 à 4) : ");
        if (scanf("%d", &nb_joueur) != 1) {
            printf("❌ Entrée invalide. Veuillez entrer un nombre.\n");
            while (getchar() != '\n');
        }
    } while (nb_joueur < 1 || nb_joueur > 4);
    while (getchar() != '\n'); // nettoyage
    return nb_joueur;
}

int demander_nombre_tresors() {
    int nb_tresors = 0;
    do {
        printf("Entrez le nombre de trésors pour gagner (minimum 1) : ");
        if (scanf("%d", &nb_tresors) != 1 || nb_tresors < 1) {
            printf("❌ Entrée invalide. Veuillez entrer un nombre valide.\n");
            while (getchar() != '\n');
        }
    } while (nb_tresors < 1);
    while (getchar() != '\n');
    return nb_tresors;
}

void traiter_commande(CommandeAnalyse cmd, Joueur joueur[], int *tour_du_joueur_x, int nb_joueur, int labyrinthe[TAILLE_PLATEAU][TAILLE_PLATEAU], bool *a_deplace, bool *a_place_tuile, bool *tour_termine) {
    int i = *tour_du_joueur_x;
    switch (cmd.type) {
        case CMD_HELP:
            afficher_regles();
            break;
        case CMD_MOVE:
            if (*a_deplace) {
                printf("⚠️ Vous vous êtes déjà déplacé ce tour-ci.\n");
            } else if (est_cheminLee(labyrinthe, joueur[i], cmd.arg1, cmd.arg2) > 0) {
                int ancienne_case = labyrinthe[cmd.arg1][cmd.arg2];
                deplacerJoueur(joueur, i, labyrinthe, cmd.arg1, cmd.arg2);
                *a_deplace = true;
                if (ancienne_case == 6) {
                    joueurSurTresor(joueur, i, labyrinthe);
                }
            } else {
                printf("❌ Déplacement invalide.\n");
            }
            afficher_labyrinthe(TAILLE_PLATEAU, labyrinthe);
            break;
        case CMD_PLACE:
            if (*a_place_tuile) {
                printf("⚠️ Vous avez déjà placé une tuile ce tour-ci.\n");
            } else if (glisser_tuile(cmd.arg1, cmd.arg2, cmd.arg3, labyrinthe, joueur, nb_joueur)) {
                *a_place_tuile = true;
            } else {
                printf("❌ Placement invalide.\n");
            }
            break;
        case CMD_SCORE:
            afficher_joueurs(joueur, nb_joueur);
            break;
        case CMD_SHOW:
            afficher_labyrinthe(TAILLE_PLATEAU, labyrinthe);
            break;
        case CMD_NEXT:
            printf("Fin du tour du joueur %d, au tour du joueur suivant !\n", *tour_du_joueur_x + 1);
            *tour_termine = true;
            (*tour_du_joueur_x)++;
            break;
        case CMD_QUIT:
            printf("Fin de partie en cours...\nAu revoir !\n\n");
            return;
        case CMD_UNKNOWN:
            printf("❌ Commande inconnue. Tapez 'help' pour la liste des commandes.\n");
            break;
        default:
            break;
    }
}

void gerer_tour(Joueur joueur[], int *tour_du_joueur, int nb_joueur, int nb_tresors, int labyrinthe[TAILLE_PLATEAU][TAILLE_PLATEAU]) {
    char commande[100];
    bool a_deplace = false;
    bool a_place_tuile = false;
    bool tour_termine = false;

    *tour_du_joueur = *tour_du_joueur % nb_joueur;
    int i = *tour_du_joueur;

    printf("\n--- 🎮 Tour du joueur %s ---\n", joueur[i].username);
    afficher_labyrinthe(TAILLE_PLATEAU, labyrinthe);
    printf("Score actuel : %d\n", joueur[i].nbTresors);

    while (!tour_termine) {
        printf("> ");
        fgets(commande, sizeof(commande), stdin);
        commande[strcspn(commande, "\n")] = '\0';  // Enlève le '\n'
        CommandeAnalyse cmd = analyser_commande(commande);
        traiter_commande(cmd, joueur, tour_du_joueur, nb_joueur, labyrinthe, &a_deplace, &a_place_tuile, &tour_termine);
    }
}

void game() {
    int labyrinthe[TAILLE_PLATEAU][TAILLE_PLATEAU];
    int nb_joueur = demander_nombre_joueurs();
    int nb_tresors = demander_nombre_tresors();
    int tour_du_joueur_x = 0;
    Joueur joueur[4];

    init_plateau(TAILLE_PLATEAU, labyrinthe);
    initJoueurs(nb_joueur, joueur, labyrinthe);
    placer_tresors(labyrinthe, nb_tresors);

    printf("\nLe jeu commence avec %d joueurs et %d trésors pour gagner ! 🎲\n", nb_joueur, nb_tresors);

    while (!winner(joueur, nb_joueur, nb_tresors)) {
        gerer_tour(joueur, &tour_du_joueur_x, nb_joueur, nb_tresors, labyrinthe);
    }

    printf("🎉 Félicitations au gagnant ! 🎉\n");
}