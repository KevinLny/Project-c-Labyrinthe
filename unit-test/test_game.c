#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/structures.h"
#include "../include/utils.h"
#include "../include/joueur.h"
#include "../include/plateau.h"
#include "../include/game.h"


// === Tests analyser_commande ===

void test_commande_place(void **state) {
    (void) state;
    CommandeAnalyse cmd = analyser_commande("place 1 2 3");
    assert_int_equal(cmd.type, CMD_PLACE);
    assert_int_equal(cmd.arg1, 1);
    assert_int_equal(cmd.arg2, 2);
    assert_int_equal(cmd.arg3, 3);
}

void test_commande_move(void **state) {
    (void) state;
    CommandeAnalyse cmd = analyser_commande("move 4 5");
    assert_int_equal(cmd.type, CMD_MOVE);
    assert_int_equal(cmd.arg1, 4);
    assert_int_equal(cmd.arg2, 5);
}

void test_commande_help(void **state) {
    (void) state;
    CommandeAnalyse cmd = analyser_commande("help");
    assert_int_equal(cmd.type, CMD_HELP);
}

void test_commande_inconnue(void **state) {
    (void) state;
    CommandeAnalyse cmd = analyser_commande("foobar 1 2 3");
    assert_int_equal(cmd.type, CMD_UNKNOWN);
}

// === Test winner ===

void test_winner_gagne(void **state) {
    (void) state;
    Joueur joueurs[1] = {{.x = 0, .y = 0, .x_init = 0, .y_init = 0, .nbTresors = 3}};
    assert_true(winner(joueurs, 1, 3));
}

void test_winner_perd(void **state) {
    (void) state;
    Joueur joueurs[1] = {{.x = 0, .y = 1, .x_init = 0, .y_init = 0, .nbTresors = 3}};
    assert_false(winner(joueurs, 1, 3));
}

// === Test demander_nombre_joueurs et demander_nombre_tresors ===

void test_demander_nombre_joueurs(void **state) {
    (void) state;
    FILE *original_stdin = stdin;
    FILE *temp = tmpfile();
    fputs("2\n", temp);
    rewind(temp);
    stdin = temp;

    int res = demander_nombre_joueurs();
    assert_int_equal(res, 2);

    fclose(temp);
    stdin = original_stdin;
}

void test_demander_nombre_tresors(void **state) {
    (void) state;
    FILE *original_stdin = stdin;
    FILE *temp = tmpfile();
    fputs("5\n", temp);
    rewind(temp);
    stdin = temp;

    int res = demander_nombre_tresors();
    assert_int_equal(res, 5);

    fclose(temp);
    stdin = original_stdin;
}

// === Mocks pour traiter_commande ===

void test_traiter_commande_move(void **state) {
    (void) state;

    int labyrinthe[TAILLE_PLATEAU][TAILLE_PLATEAU] = {
        {0,0,0,0,0,0,0,0,0},
        {0,2,1,1,0,1,1,1,0},
        {0,1,0,1,0,1,0,1,0},
        {0,1,1,1,0,1,1,1,0},
        {0,0,0,0,0,0,0,0,0},
        {0,1,1,1,0,1,1,1,0},
        {0,1,0,1,0,1,0,1,0},
        {0,1,1,1,0,1,1,1,0},
        {0,0,0,0,0,0,0,0,0}
    };

    Joueur joueurs[1] = {{
        .x = 1,
        .y = 1,
        .x_init = 1,
        .y_init = 1,
        .nbTresors = 0
    }};

    CommandeAnalyse cmd = {
        .type = CMD_MOVE,
        .arg1 = 1,
        .arg2 = 2
    };

    int tour = 0;
    bool a_deplace = false;
    bool a_place_tuile = false;
    bool tour_termine = false;

    traiter_commande(cmd, joueurs, &tour, 1, labyrinthe, &a_deplace, &a_place_tuile, &tour_termine);

    assert_int_equal(labyrinthe[1][2], 2); // vérifier que le joueur s’est déplacé
}


void test_traiter_commande_place(void **state) {
    (void) state;

    // Labyrinthe initial (peut être simple ici)
    int labyrinthe[TAILLE_PLATEAU][TAILLE_PLATEAU] = {
        {0,0,0,0,0,0,0,0,0},
        {0,1,1,1,1,1,1,1,0},
        {0,1,1,1,1,1,1,1,0},
        {0,1,1,1,1,1,1,1,0},
        {0,1,1,1,1,1,1,1,0},
        {0,1,1,1,1,1,1,1,0},
        {0,1,1,1,1,1,1,1,0},
        {0,1,1,1,1,1,1,1,0},
        {0,0,0,0,0,0,0,0,0}
    };

    Joueur joueurs[1] = {{.x = 1, .y = 1, .x_init = 1, .y_init = 1, .nbTresors = 0}};

    CommandeAnalyse cmd = {
        .type = CMD_PLACE,
        .arg1 = 2,  // ligne ou colonne à insérer
        .arg2 = 1,  // 1 = vers le bas/droite, 0 = vers le haut/gauche (selon ta logique)
        .arg3 = 0   // position ou direction optionnelle
    };

    int tour = 0;
    bool a_deplace = false;
    bool a_place_tuile = false;
    bool tour_termine = false;

    // Appel
    traiter_commande(cmd, joueurs, &tour, 1, labyrinthe, &a_deplace, &a_place_tuile, &tour_termine);

    assert_true(a_place_tuile);
}

void test_traiter_commande_next(void **state) {
    (void) state;

    int labyrinthe[TAILLE_PLATEAU][TAILLE_PLATEAU] = {{0}};
    Joueur joueurs[1] = {{0}};
    CommandeAnalyse cmd = {.type = CMD_NEXT};

    int tour = 0;
    bool a_deplace = false, a_place_tuile = false, tour_termine = false;

    traiter_commande(cmd, joueurs, &tour, 1, labyrinthe, &a_deplace, &a_place_tuile, &tour_termine);

    assert_true(tour_termine);
}

void test_traiter_commande_show(void **state) {
    (void) state;

    int labyrinthe[TAILLE_PLATEAU][TAILLE_PLATEAU] = {{0}};
    Joueur joueurs[1] = {{0}};
    CommandeAnalyse cmd = {.type = CMD_SHOW};

    int tour = 0;
    bool a_deplace = false, a_place_tuile = false, tour_termine = false;

    traiter_commande(cmd, joueurs, &tour, 1, labyrinthe, &a_deplace, &a_place_tuile, &tour_termine);

    assert_false(a_deplace);
    assert_false(a_place_tuile);
    assert_false(tour_termine);
}

void test_traiter_commande_help(void **state) {
    (void) state;

    int labyrinthe[TAILLE_PLATEAU][TAILLE_PLATEAU] = {{0}};
    Joueur joueurs[1] = {{0}};
    CommandeAnalyse cmd = {.type = CMD_HELP};

    int tour = 0;
    bool a_deplace = false, a_place_tuile = false, tour_termine = false;

    traiter_commande(cmd, joueurs, &tour, 1, labyrinthe, &a_deplace, &a_place_tuile, &tour_termine);

    assert_false(a_deplace);
    assert_false(a_place_tuile);
    assert_false(tour_termine);
}

void test_traiter_commande_unknown(void **state) {
    (void) state;

    int labyrinthe[TAILLE_PLATEAU][TAILLE_PLATEAU] = {{0}};
    Joueur joueurs[1] = {{.x = 1, .y = 1}};
    CommandeAnalyse cmd = {.type = CMD_UNKNOWN};  // Type inconnu

    int tour = 0;
    bool a_deplace = false;
    bool a_place_tuile = false;
    bool tour_termine = false;

    traiter_commande(cmd, joueurs, &tour, 1, labyrinthe, &a_deplace, &a_place_tuile, &tour_termine);

    assert_false(a_deplace);
    assert_false(a_place_tuile);
    assert_false(tour_termine);
    // Et on vérifie que les coordonnées n'ont pas changé :
    assert_int_equal(joueurs[0].x, 1);
    assert_int_equal(joueurs[0].y, 1);
}


void test_traiter_commande_score(void **state) {
    (void) state;

    int labyrinthe[TAILLE_PLATEAU][TAILLE_PLATEAU] = {{0}};
    Joueur joueurs[1] = {{.nbTresors = 2}};
    CommandeAnalyse cmd = {.type = CMD_SCORE};

    int tour = 0;
    bool a_deplace = false, a_place_tuile = false, tour_termine = false;

    traiter_commande(cmd, joueurs, &tour, 1, labyrinthe, &a_deplace, &a_place_tuile, &tour_termine);

    // Aucun assert ici, car afficher_score écrit sur stdout, mais pas d'effet d'état
    assert_false(a_deplace);
    assert_false(a_place_tuile);
    assert_false(tour_termine);
}




void test_gerer_tour_simple_next(void **state) {
    (void) state;

    // Simule l'entrée utilisateur "next\n"
    const char *input = "next\n";
    FILE *input_stream = fmemopen((void *)input, strlen(input), "r");
    assert_non_null(input_stream);

    // Sauvegarde l'ancien stdin
    FILE *original_stdin = stdin;
    stdin = input_stream;

    // Initialisation du labyrinthe et des joueurs
    int labyrinthe[TAILLE_PLATEAU][TAILLE_PLATEAU] = {
        {0,0,0,0,0,0,0,0,0},
        {0,1,1,1,1,1,1,1,0},
        {0,1,1,1,1,1,1,1,0},
        {0,1,1,1,1,1,1,1,0},
        {0,1,1,1,1,1,1,1,0},
        {0,1,1,1,1,1,1,1,0},
        {0,1,1,1,1,1,1,1,0},
        {0,1,1,1,1,1,1,1,0},
        {0,0,0,0,0,0,0,0,0}
    };

    Joueur joueurs[1] = {{
        .x = 4,
        .y = 4,
        .x_init = 4,
        .y_init = 4,
        .nbTresors = 0,
        .username = "Joueur1"
    }};

    int tour = 0;

    // Appel de la fonction à tester
    gerer_tour(joueurs, &tour, 1, 0, labyrinthe);

    // Vérifie que le tour a bien été terminé
    assert_int_equal(tour, 1); // car CMD_NEXT incrémente le tour

    // Restaure stdin
    stdin = original_stdin;
    fclose(input_stream);
}

void test_afficher_regles(void **state) {
    (void) state;

    // Rediriger stdout vers un fichier temporaire
    freopen("output_regles.txt", "w+", stdout);
    afficher_regles();
    fflush(stdout);
    freopen("/dev/tty", "w", stdout); // Restaure stdout

    // Lire le fichier temporaire
    FILE *file = fopen("output_regles.txt", "r");
    assert_non_null(file);

    char output[2048] = {0};
    fread(output, sizeof(char), sizeof(output) - 1, file);
    fclose(file);

    // Vérifications : quelques commandes clés
    assert_non_null(strstr(output, "Commandes disponibles"));
    assert_non_null(strstr(output, "move x y"));
    assert_non_null(strstr(output, "place x y d"));
    assert_non_null(strstr(output, "next"));
    assert_non_null(strstr(output, "score"));
    assert_non_null(strstr(output, "show"));
    assert_non_null(strstr(output, "help"));
    assert_non_null(strstr(output, "quit"));
}