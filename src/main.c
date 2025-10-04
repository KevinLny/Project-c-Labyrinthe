#include <stdio.h>
#include <string.h>
#include "../include/game.h"
#include "../include/joueur.h"
#include "../include/plateau.h"

int main() {
    printf(" _       ____  ____   __ __  ____   ____  ____   ______  __ __    ___ \n");
    printf("| |     /    ||    \\ |  |  ||    \\ |    ||    \\ |      ||  |  |  /  _]\n");
    printf("| |    |  o  ||  o  )|  |  ||  D  ) |  | |  _  ||      ||  |  | /  [_ \n");
    printf("| |___ |     ||     ||  ~  ||    /  |  | |  |  ||_|  |_||  _  ||    _]\n");
    printf("|     ||  _  ||  O  ||___, ||    \\  |  | |  |  |  |  |  |  |  ||   [_ \n");
    printf("|     ||  |  ||     ||     ||  .  \\ |  | |  |  |  |  |  |  |  ||     |\n");
    printf("|_____||__|__||_____||____/ |__|\\_\\|____||__|__|  |__|  |__|__||_____|\n");
    printf("\n");
    
    

    printf("Bienvenue dans le jeu du Labyrinthe !\n");
    printf("Les règles sont simples :\n");
    printf("- Pour gagner, récupérez les trésors (symbolisés par la lettre 'T') disséminés sur la carte,\n");
    printf("  puis retournez à votre position de départ.\n");
    printf("- À chaque tour, vous pouvez effectuer plusieurs actions :\n");
    printf("  vous déplacer là où c'est possible, placer un chemin ou construire un mur.\n");
    printf("- Utilisez ces actions stratégiquement pour vous faciliter l'accès aux trésors,\n");
    printf("  ou pour compliquer la tâche à vos adversaires !\n");
    printf("Bonne chance... et que le meilleur gagne !\n\n\n");

    game();
    return 0;
}
