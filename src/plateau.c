#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/plateau.h"

void init_plateau(int n, int labyrinthe[TAILLE_PLATEAU][TAILLE_PLATEAU]) {
    if (n < 2) {
        printf("La taille du labyrinthe doit être au moins 2.\n");
        return;
    }

    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if(i == 0 || j == 0 || i == n-1 || j == n-1)
                labyrinthe[i][j] = 0; // Init at 0 
            else 
                labyrinthe[i][j] = rand() % 2; // Générer aléatoirement 0 ou 1
        }
    }

    if (n > 2) {
        labyrinthe[1][1] = 1;
        labyrinthe[1][n-2] = 1;
        labyrinthe[n-2][1] = 1;
        labyrinthe[n-2][n-2] = 1;
    }
}

// Sens = 0 gauche/haut, sens = 1 droite/bas
int glisser_tuile(int numero, int sens, int tuile, int labyrinthe[TAILLE_PLATEAU][TAILLE_PLATEAU], Joueur joueurs[], int nb_joueurs) {
    int tmp;
    int x_out = -1, y_out = -1;

    // Sauvegarde des positions initiales des joueurs
    int old_x[nb_joueurs], old_y[nb_joueurs];
    for (int j = 0; j < nb_joueurs; j++) {
        old_x[j] = joueurs[j].x;
        old_y[j] = joueurs[j].y;
    }

    switch (numero) {
        case 1:
        case 2:
        case 3: {
            int col = 2 * numero;
            if (sens == 0) { // HAUT
                tmp = labyrinthe[TAILLE_PLATEAU - 2][col];
                for (int i = TAILLE_PLATEAU - 2; i > 0; i--) {
                    labyrinthe[i][col] = labyrinthe[i - 1][col];
                }
                labyrinthe[1][col] = tuile;
                x_out = TAILLE_PLATEAU - 2;
                y_out = col;

                // Déplacement des joueurs
                for (int j = 0; j < nb_joueurs; j++) {
                    if (old_y[j] == col && old_x[j] > 0 && old_x[j] < TAILLE_PLATEAU - 1)
                        joueurs[j].x++;
                }

            } else if (sens == 1) { // BAS
                tmp = labyrinthe[1][col];
                for (int i = 1; i < TAILLE_PLATEAU - 1; i++) {
                    labyrinthe[i][col] = labyrinthe[i + 1][col];
                }
                labyrinthe[TAILLE_PLATEAU - 2][col] = tuile;
                x_out = 1;
                y_out = col;

                for (int j = 0; j < nb_joueurs; j++) {
                    if (old_y[j] == col && old_x[j] > 0 && old_x[j] < TAILLE_PLATEAU - 1)
                        joueurs[j].x--;
                }

            } else {
                printf("\nERREUR - Sens invalide.\n");
                return 0;
            }
            break;
        }

        case 4:
        case 5:
        case 6: {
            int lig = 2 * (numero - 3);
            if (sens == 0) { // GAUCHE
                tmp = labyrinthe[lig][TAILLE_PLATEAU - 2];
                for (int i = TAILLE_PLATEAU - 2; i > 0; i--) {
                    labyrinthe[lig][i] = labyrinthe[lig][i - 1];
                }
                labyrinthe[lig][1] = tuile;
                x_out = lig;
                y_out = TAILLE_PLATEAU - 2;

                for (int j = 0; j < nb_joueurs; j++) {
                    if (old_x[j] == lig && old_y[j] > 0 && old_y[j] < TAILLE_PLATEAU - 1)
                        joueurs[j].y++;
                }

            } else if (sens == 1) { // DROITE
                tmp = labyrinthe[lig][1];
                for (int i = 1; i < TAILLE_PLATEAU - 1; i++) {
                    labyrinthe[lig][i] = labyrinthe[lig][i + 1];
                }
                labyrinthe[lig][TAILLE_PLATEAU - 2] = tuile;
                x_out = lig;
                y_out = 1;

                for (int j = 0; j < nb_joueurs; j++) {
                    if (old_x[j] == lig && old_y[j] > 0 && old_y[j] < TAILLE_PLATEAU - 1)
                        joueurs[j].y--;
                }

            } else {
                printf("\nERREUR - Sens invalide.\n");
                return 0;
            }
            break;
        }

        default:
            printf("\nERREUR - Veuillez entrer un numéro entre 1 et 6.\n");
            return 0;
    }

    // Traitement des joueurs réellement éjectés
    for (int j = 0; j < nb_joueurs; j++) {
        if (old_x[j] == x_out && old_y[j] == y_out) {
            // Réinitialisation
            switch (j) {
                case 0:
                    joueurs[j].x = 1; joueurs[j].y = 1;
                    labyrinthe[1][1] = j + 2;
                    break;
                case 1:
                    joueurs[j].x = 1; joueurs[j].y = 7;
                    labyrinthe[1][7] = j + 2;
                    break;
                case 2:
                    joueurs[j].x = 7; joueurs[j].y = 1;
                    labyrinthe[7][1] = j + 2;
                    break;
                case 3:
                    joueurs[j].x = 7; joueurs[j].y = 7;
                    labyrinthe[7][7] = j + 2;
                    break;
            }
            printf("Joueur %s a été éjecté du labyrinthe ! Coordonnées réinitialisées.\n", joueurs[j].username);
        }
    }

    // Remettre un trésor si éjecté
    if (tmp == 6) {
        int placé = 0;
        while (!placé) {
            int x = rand() % (TAILLE_PLATEAU - 2) + 1;
            int y = rand() % (TAILLE_PLATEAU - 2) + 1;
            if (labyrinthe[x][y] == 1) {
                labyrinthe[x][y] = 6;
                placé = 1;
                printf("Un trésor a été replacé sur la case (%d, %d).\n", x, y);
            }
        }
    }

    return 1;
}


bool placer_tresors(int labyrinthe[TAILLE_PLATEAU][TAILLE_PLATEAU], int nb_tresors) {
    srand(time(NULL));
    int tries = 0;
    int max_tries = 49; //permet d'éviter la boucle infinie

    int pos_joueurs[4][2] = {
        {1, 1},
        {1, TAILLE_PLATEAU - 2},
        {TAILLE_PLATEAU - 2, 1},
        {TAILLE_PLATEAU - 2, TAILLE_PLATEAU - 2}
    };

    while (nb_tresors > 0 && tries < max_tries) {
        int x = 1 + rand() % (TAILLE_PLATEAU - 2);
        int y = 1 + rand() % (TAILLE_PLATEAU - 2);

        bool est_coin = false;
        for (int i = 0; i < 4; i++) {
            if (x == pos_joueurs[i][0] && y == pos_joueurs[i][1]) {
                est_coin = true;
                break;
            }
        }

        if (!est_coin && labyrinthe[x][y] == 1) {
            labyrinthe[x][y] = 6;  // Code pour trésor
            nb_tresors--;
        }
    }

    if (nb_tresors > 0) {
        printf("Impossible de placer tous les trésors.\n");
        return 0;
    }
    return 1;
}

bool est_valide(int x, int y, int labyrinthe[TAILLE_PLATEAU][TAILLE_PLATEAU], bool visited[TAILLE_PLATEAU][TAILLE_PLATEAU]) {
    return x >= 0 && x < TAILLE_PLATEAU &&
           y >= 0 && y < TAILLE_PLATEAU &&
           !visited[x][y] &&
           (labyrinthe[x][y] == 1 || labyrinthe[x][y] == 6);
}

int est_cheminLee(int labyrinthe[TAILLE_PLATEAU][TAILLE_PLATEAU], Joueur joueur, int x, int y) {
    bool visited[TAILLE_PLATEAU][TAILLE_PLATEAU] = {false};

    // Mouvements : haut, bas, gauche, droite
    int dx[] = { -1, 1, 0, 0 };
    int dy[] = { 0, 0, -1, 1 };

    Cell queue[TAILLE_PLATEAU * TAILLE_PLATEAU];
    int front = 0, rear = 0;

    // Démarrer depuis la position du joueur
    queue[rear++] = (Cell){joueur.x, joueur.y, 0};
    visited[joueur.x][joueur.y] = true;

    while (front < rear) {
        Cell current = queue[front++];

        // Si on atteint la destination
        if (current.x == x && current.y == y) {
            return current.dist;
        }

        // Explorer les 4 voisins
        for (int i = 0; i < 4; i++) {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];

            if (est_valide(nx, ny, labyrinthe, visited)) {
                visited[nx][ny] = true;
                queue[rear++] = (Cell){nx, ny, current.dist + 1};
            }
        }
    }

    return -1; // Aucun chemin trouvé
}
