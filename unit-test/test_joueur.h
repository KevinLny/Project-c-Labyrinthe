// test_JOUEUR.h
#ifndef TEST_JOUEUR_H
#define TEST_JOUEUR_H

#include "../include/structures.h"
#include "../include/affichage.h"
#include "../include/plateau.h"

void placer_tresors_test(int labyrinthe[TAILLE_PLATEAU][TAILLE_PLATEAU], int nb);
void test_initJoueurs(void **state);
void test_deplacerJoueur(void **state);
void test_joueurSurTresor(void **state);

#endif // TEST_JOUEUR_H
