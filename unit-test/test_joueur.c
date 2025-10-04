#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "../include/structures.h"
#include "../include/plateau.h"
#include "../include/affichage.h"
#include "../include/joueur.h"

// ----------- Test initJoueurs ---------------------
void test_initJoueurs(void **state) {
    (void)state;

    Joueur joueurs[2];
    int labyrinthe[TAILLE_PLATEAU][TAILLE_PLATEAU] = {0};

    const char *input = "Alice\nBob\n";
    FILE *input_stream = fmemopen((void *)input, strlen(input), "r");
    assert_non_null(input_stream);

    FILE *original_stdin = stdin;
    stdin = input_stream;

    initJoueurs(2, joueurs, labyrinthe);

    fclose(input_stream);
    stdin = original_stdin;

    assert_string_equal(joueurs[0].username, "Alice");
    assert_int_equal(joueurs[0].x, 1);
    assert_int_equal(joueurs[0].y, 1);
    assert_int_equal(labyrinthe[1][1], 2);

    assert_string_equal(joueurs[1].username, "Bob");
    assert_int_equal(joueurs[1].x, 1);
    assert_int_equal(joueurs[1].y, TAILLE_PLATEAU - 2);
    assert_int_equal(labyrinthe[1][TAILLE_PLATEAU - 2], 3);
}

// ----------- Test deplacerJoueur ---------------------
void test_deplacerJoueur(void **state) {
    (void)state;

    Joueur joueurs[1] = {
        {.username = "Alice", .x = 1, .y = 1}
    };
    int labyrinthe[TAILLE_PLATEAU][TAILLE_PLATEAU] = {0};
    labyrinthe[1][1] = 2;

    deplacerJoueur(joueurs, 0, labyrinthe, 2, 2);

    assert_int_equal(labyrinthe[1][1], 1);
    assert_int_equal(labyrinthe[2][2], 2);
    assert_int_equal(joueurs[0].x, 2);
    assert_int_equal(joueurs[0].y, 2);
}

// ----------- Test joueurSurTresor ---------------------
void test_joueurSurTresor(void **state) {
    (void)state;
    int ancienne_case;

    // Initialisation du labyrinthe
    int labyrinthe[TAILLE_PLATEAU][TAILLE_PLATEAU] = {
        {0,0,0,0,0,0,0,0,0},
        {0,2,6,1,0,1,6,3,0},
        {0,1,1,1,0,1,1,1,0},
        {0,1,1,1,0,1,1,1,0},
        {0,0,0,0,0,0,0,0,0},
        {0,1,1,1,0,1,1,1,0},
        {0,1,0,1,0,1,0,1,0},
        {0,1,1,1,0,1,1,1,0},
        {0,0,0,0,0,0,0,0,0}
    };

    // Initialisation des joueurs
    Joueur joueurs[2] = {
        {.username = "Alice", .x = 1, .y = 1, .nbTresors = 0}
    };

    // Redirection stdout vers fichier
    freopen("output_joueur_tresor.txt", "w+", stdout);

    // Seul Bob est sur un trésor
    ancienne_case = labyrinthe[1][2];
    deplacerJoueur(joueurs,0, labyrinthe, 1, 2); // Passer par pointeur
    if(ancienne_case == 6){
        joueurSurTresor(joueurs, 0, labyrinthe);
    }

    fflush(stdout);
    freopen("/dev/tty", "w", stdout);  // Restaure stdout

    // Vérification du fichier de sortie
    FILE *file = fopen("output_joueur_tresor.txt", "r");
    assert_non_null(file);

    char output[512];
    fread(output, sizeof(char), sizeof(output) - 1, file);
    fclose(file);

    // Vérifie les effets de la fonction
    assert_int_equal(joueurs[0].nbTresors, 1);  // Alice n'était pas sur un trésor
    assert_true(strstr(output, "Le joueur Alice a trouvé un trésor") != NULL);
}