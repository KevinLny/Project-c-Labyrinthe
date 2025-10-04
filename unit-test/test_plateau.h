#ifndef TEST_PLATEAU_H
#define TEST_PLATEAU_H

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdbool.h>
#include <cmocka.h>

void test_init_plateau_size_too_small(void **state);
void test_init_plateau_valid(void **state);

void test_glisser_tuile_cases_valides(void **state);
void test_glisser_tuile_tresor_ejecte(void **state);
void test_glisser_tuile_numero_invalide(void **state);
void test_glisser_tuile_sens_invalide(void **state);
void test_placer_tresors_normal(void **state);
void test_placer_tresors_impossible(void **state);
void test_est_cheminLee_valide(void **state);
void test_est_cheminLee_bloque(void **state);
void test_glisser_tuile_joueur_0_ejecte(void **state);
void test_glisser_tuile_joueur_1_ejecte(void **state);
void test_glisser_tuile_joueur_2_ejecte(void **state);
void test_glisser_tuile_joueur_3_ejecte(void **state);

#endif