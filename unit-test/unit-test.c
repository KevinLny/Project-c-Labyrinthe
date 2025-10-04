#include <stdio.h>
#include <string.h>

#include "test_joueur.h"
#include "test_plateau.h"
#include "test_affichage.h"
#include "test_game.h"
#include "test_utils.h"

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>


int main(void)
{

    const struct CMUnitTest tests[]=
    {
        // TEST-UNITAIRE AFFICHAGE
        cmocka_unit_test(test_afficher_labyrinthe_simple),
        cmocka_unit_test(test_afficher_joueurs_simple),

        // TEST-UNITAIRE JOUEUR
        cmocka_unit_test(test_initJoueurs),
        cmocka_unit_test(test_deplacerJoueur),
        cmocka_unit_test(test_joueurSurTresor),

        //TEST-UNITAIRE PLATEAU
        cmocka_unit_test(test_init_plateau_size_too_small),
        cmocka_unit_test(test_init_plateau_valid),
        cmocka_unit_test(test_glisser_tuile_cases_valides),
        cmocka_unit_test(test_glisser_tuile_tresor_ejecte),
        cmocka_unit_test(test_glisser_tuile_numero_invalide),
        cmocka_unit_test(test_glisser_tuile_sens_invalide),
        cmocka_unit_test(test_placer_tresors_normal),
        cmocka_unit_test(test_est_cheminLee_valide),
        cmocka_unit_test(test_est_cheminLee_bloque),
        cmocka_unit_test(test_glisser_tuile_joueur_0_ejecte),
        cmocka_unit_test(test_glisser_tuile_joueur_1_ejecte),
        cmocka_unit_test(test_glisser_tuile_joueur_2_ejecte),
        cmocka_unit_test(test_glisser_tuile_joueur_3_ejecte),

        //TEST-UNITAIRE GAME
        cmocka_unit_test(test_commande_place),
        cmocka_unit_test(test_commande_move),
        cmocka_unit_test(test_commande_help),
        cmocka_unit_test(test_commande_inconnue),
        cmocka_unit_test(test_winner_gagne),
        cmocka_unit_test(test_winner_perd),
        cmocka_unit_test(test_demander_nombre_joueurs),
        cmocka_unit_test(test_demander_nombre_tresors),
        cmocka_unit_test(test_traiter_commande_move),
        cmocka_unit_test(test_traiter_commande_place),
        cmocka_unit_test(test_traiter_commande_next),
        cmocka_unit_test(test_traiter_commande_score),
        cmocka_unit_test(test_traiter_commande_show),
        cmocka_unit_test(test_traiter_commande_help),
        cmocka_unit_test(test_traiter_commande_unknown),
        cmocka_unit_test(test_gerer_tour_simple_next),
        cmocka_unit_test(test_afficher_regles),


        //TEST-UNITAIRE UTILS
        cmocka_unit_test(test_afficher_matrice),


        
    };
    return cmocka_run_group_tests_name("Test module ...",tests,NULL,NULL);
}