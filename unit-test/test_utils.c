#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include <string.h>

#include "../include/utils.h"

void test_afficher_matrice(void **state) {
        (void)state;

    // Préparation de la matrice 3x3 (adapte TAILLE_PLATEAU si nécessaire)
    int labyrinthe[TAILLE_PLATEAU][TAILLE_PLATEAU] = {0};
    labyrinthe[0][0] = 1;
    labyrinthe[1][1] = 2;
    labyrinthe[2][2] = 3;

    // Redirection de stdout
    char buffer[1024];
    FILE *original_stdout = stdout;
    freopen("temp_output.txt", "w+", stdout);

    afficher_matrice(labyrinthe);

    fflush(stdout);
    fseek(stdout, 0, SEEK_SET);
    fread(buffer, sizeof(char), sizeof(buffer) - 1, stdout);
    buffer[sizeof(buffer) - 1] = '\0';

    // Remettre stdout à la normale
    fclose(stdout);
    stdout = original_stdout;

    // Vérifie que des chiffres spécifiques apparaissent
    assert_non_null(strstr(buffer, " 1 "));
    assert_non_null(strstr(buffer, " 2 "));
    assert_non_null(strstr(buffer, " 3 "));
}
