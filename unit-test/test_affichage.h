// test_affichage.h
#ifndef TEST_AFFICHAGE_H
#define TEST_AFFICHAGE_H

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

void test_afficher_labyrinthe_simple(void **state);
void test_afficher_joueurs_simple(void **state);

#endif // TEST_AFFICHAGE_H
