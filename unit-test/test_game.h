#ifndef TEST_GAME_H
#define TEST_GAME_H

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdbool.h>
#include <cmocka.h>

void test_commande_place(void **state);
void test_commande_move(void **state);
void test_commande_help(void **state);
void test_commande_inconnue(void **state);
void test_winner_gagne(void **state);
void test_winner_perd(void **state);
void test_demander_nombre_joueurs(void **state);
void test_demander_nombre_tresors(void **state);
void test_traiter_commande_move(void **state);
void test_traiter_commande_place(void **state);
void test_traiter_commande_next(void **state);
void test_traiter_commande_score(void **state);
void test_traiter_commande_show(void **state);
void test_traiter_commande_help(void **state);
void test_traiter_commande_unknown(void **state);
void test_gerer_tour_simple_next(void **state);
void test_afficher_regles(void **state);

#endif