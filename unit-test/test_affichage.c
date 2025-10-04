#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>
#include <stdio.h>
#include <string.h>

#include "../include/affichage.h" 


void test_afficher_labyrinthe_simple(void **state) {
    (void) state;

    int labyrinthe[TAILLE_PLATEAU][TAILLE_PLATEAU] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 2, 3, 4, 0, 5, 6, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0, 1, 1, 1, 0},
        {0, 1, 0, 1, 0, 1, 0, 1, 0},
        {0, 1, 1, 1, 0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    // Redirection stdout vers un fichier temporaire
    freopen("output_labyrinthe_pions.txt", "w+", stdout);
    afficher_labyrinthe(TAILLE_PLATEAU, labyrinthe);
    fflush(stdout);
    freopen("/dev/tty", "w", stdout); // Restaure stdout

    // Lecture du fichier temporaire
    FILE *file = fopen("output_labyrinthe_pions.txt", "r");
    assert_non_null(file);

    char output[2048] = {0};
    fread(output, sizeof(char), sizeof(output) - 1, file);
    fclose(file);
}


void test_afficher_joueurs_simple(void **state) {
    (void) state;

    Joueur joueurs[2] = {
        {.username = "Alice", .x = 1, .y = 1, .nbTresors = 2},
        {.username = "Bob", .x = 7, .y = 7, .nbTresors = 1}
    };

    freopen("output_joueurs.txt", "w+", stdout);
    afficher_joueurs(joueurs, 2);
    fflush(stdout);
    freopen("/dev/tty", "w", stdout);

    FILE *file = fopen("output_joueurs.txt", "r");
    assert_non_null(file);

    char output[1024];
    fread(output, sizeof(char), sizeof(output) - 1, file);
    fclose(file);

    assert_true(strstr(output, "Alice") != NULL);
    assert_true(strstr(output, "Bob") != NULL);
    assert_true(strstr(output, "x = 1") != NULL);
    assert_true(strstr(output, "x = 7") != NULL);
}
