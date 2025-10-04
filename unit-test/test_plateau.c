#include <string.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "../include/plateau.h"

void test_init_plateau_size_too_small(void  **state) {
    (void)state;
    int lab[TAILLE_PLATEAU][TAILLE_PLATEAU] = {0};
    init_plateau(1, lab);
    for (int i = 0; i < TAILLE_PLATEAU; ++i)
        for (int j = 0; j < TAILLE_PLATEAU; ++j)
            assert_int_equal(lab[i][j], 0);
}

void test_init_plateau_valid(void  **state) {
    (void)state;
    int lab[TAILLE_PLATEAU][TAILLE_PLATEAU] = {0};
    init_plateau(TAILLE_PLATEAU, lab);
    assert_int_equal(lab[1][1], 1);
    assert_int_equal(lab[1][TAILLE_PLATEAU-2], 1);
    assert_int_equal(lab[TAILLE_PLATEAU-2][1], 1);
    assert_int_equal(lab[TAILLE_PLATEAU-2][TAILLE_PLATEAU-2], 1);
}
// TEST GLISSER TUILE

void test_glisser_tuile_cases_valides(void **state) {
    (void) state;

    for (int numero = 1; numero <= 6; numero++) {
        for (int sens = 0; sens <= 1; sens++) {
            int labyrinthe[TAILLE_PLATEAU][TAILLE_PLATEAU];
            memset(labyrinthe, 1, sizeof(labyrinthe));
            labyrinthe[4][4] = 6; // trésor au centre

            Joueur joueurs[1] = {{
                .x = 4,
                .y = 4,
                .x_init = 4,
                .y_init = 4,
                .nbTresors = 0,
                .username = "Test"
            }};

            int result = glisser_tuile(numero, sens, 1, labyrinthe, joueurs, 1);
            assert_int_equal(result, 1);
        }
    }
}
void test_glisser_tuile_tresor_ejecte(void **state) {
    (void) state;

    int labyrinthe[TAILLE_PLATEAU][TAILLE_PLATEAU];
    memset(labyrinthe, 1, sizeof(labyrinthe));

    // Place un trésor sur la case éjectée pour la colonne 2*1 = 2, en bas = ligne 1
    labyrinthe[1][2] = 6;

    Joueur joueurs[1] = {{
        .x = 2,
        .y = 2,
        .x_init = 2,
        .y_init = 2,
        .nbTresors = 0,
        .username = "Test"
    }};

    int result = glisser_tuile(1, 1, 1, labyrinthe, joueurs, 1);
    assert_int_equal(result, 1);

    // Vérifie qu’un trésor a été replacé quelque part
    int count = 0;
    for (int i = 1; i < TAILLE_PLATEAU - 1; i++) {
        for (int j = 1; j < TAILLE_PLATEAU - 1; j++) {
            if (labyrinthe[i][j] == 6)
                count++;
        }
    }
    assert_int_equal(count, 1);
}

void test_glisser_tuile_numero_invalide(void **state) {
    (void) state;

    int labyrinthe[TAILLE_PLATEAU][TAILLE_PLATEAU];
    Joueur joueurs[1];

    int result = glisser_tuile(0, 0, 1, labyrinthe, joueurs, 1); // Invalide
    assert_int_equal(result, 0);
}

void test_glisser_tuile_sens_invalide(void **state) {
    (void) state;

    int labyrinthe[TAILLE_PLATEAU][TAILLE_PLATEAU];
    Joueur joueurs[1];

    int result = glisser_tuile(2, 2, 1, labyrinthe, joueurs, 1); // Invalide
    assert_int_equal(result, 0);
}

void test_placer_tresors_normal(void **state) {
    (void)state;
    int lab[TAILLE_PLATEAU][TAILLE_PLATEAU] = {0};
    init_plateau(TAILLE_PLATEAU, lab);
    int res = placer_tresors(lab, 5);
    assert_true(res);
}

void test_est_cheminLee_valide(void **state) {
    (void)state;
    Joueur j = {.x = 1, .y = 1};
    int lab[TAILLE_PLATEAU][TAILLE_PLATEAU] = {0};
    for (int i = 1; i < TAILLE_PLATEAU-1; i++)
        for (int j = 1; j < TAILLE_PLATEAU-1; j++)
            lab[i][j] = 1;
    int dist = est_cheminLee(lab, j, 1, 2);
    assert_int_equal(dist, 1);
}


void test_glisser_tuile_joueur_0_ejecte(void **state) {
    (void)state;
    int labyrinthe[TAILLE_PLATEAU][TAILLE_PLATEAU] = {0};
    Joueur joueurs[4] = {0};
    joueurs[0].x = 7;
    joueurs[0].y = 2;
    strcpy(joueurs[0].username, "J0");
    labyrinthe[7][2] = 1;

    int result = glisser_tuile(1, 0, 3, labyrinthe, joueurs, 4);

    assert_int_equal(result, 1);
    assert_int_equal(joueurs[0].x, 1);
    assert_int_equal(joueurs[0].y, 1);
    assert_int_equal(labyrinthe[1][1], 2); // j + 2
}

void test_glisser_tuile_joueur_1_ejecte(void **state) {
    (void)state;
    int labyrinthe[TAILLE_PLATEAU][TAILLE_PLATEAU] = {0};
    Joueur joueurs[4] = {0};
    joueurs[1].x = 7;
    joueurs[1].y = 2;
    strcpy(joueurs[1].username, "J1");
    labyrinthe[7][2] = 1;

    int result = glisser_tuile(1, 0, 3, labyrinthe, joueurs, 4);

    assert_int_equal(result, 1);
    assert_int_equal(joueurs[1].x, 1);
    assert_int_equal(joueurs[1].y, 7);
    assert_int_equal(labyrinthe[1][7], 3);
}

void test_glisser_tuile_joueur_2_ejecte(void **state) {
    (void)state;
    int labyrinthe[TAILLE_PLATEAU][TAILLE_PLATEAU] = {0};
    Joueur joueurs[4] = {0};
    joueurs[2].x = 7;
    joueurs[2].y = 2;
    strcpy(joueurs[2].username, "J2");
    labyrinthe[7][2] = 1;

    int result = glisser_tuile(1, 0, 3, labyrinthe, joueurs, 4);

    assert_int_equal(result, 1);
    assert_int_equal(joueurs[2].x, 7);
    assert_int_equal(joueurs[2].y, 1);
    assert_int_equal(labyrinthe[7][1], 4);
}

void test_glisser_tuile_joueur_3_ejecte(void **state) {
    (void)state;
    int labyrinthe[TAILLE_PLATEAU][TAILLE_PLATEAU] = {0};
    Joueur joueurs[4] = {0};
    joueurs[3].x = 7;
    joueurs[3].y = 2;
    strcpy(joueurs[3].username, "J3");
    labyrinthe[7][2] = 1;

    int result = glisser_tuile(1, 0, 3, labyrinthe, joueurs, 4);

    assert_int_equal(result, 1);
    assert_int_equal(joueurs[3].x, 7);
    assert_int_equal(joueurs[3].y, 7);
    assert_int_equal(labyrinthe[7][7], 5);
}

void test_est_cheminLee_bloque(void  **state) {
    Joueur j = {.x = 1, .y = 1};
    int lab[TAILLE_PLATEAU][TAILLE_PLATEAU] = {0};
    lab[1][1] = 1;
    lab[1][2] = 0;
    lab[2][1] = 0;
    int dist = est_cheminLee(lab, j, 2, 2);
    assert_int_equal(dist, -1);
}