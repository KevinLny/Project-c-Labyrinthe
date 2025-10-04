# Bienvenue dans le projet Labyrinthe

Bienvenue dans la documentation de notre jeu **Labyrinthe**, développé en langage C. Ce projet met en avant l'utilisation de structures dynamiques, de la gestion des joueurs et du plateau, ainsi que des algorithmes d'interaction. 

## 🔗 Navigation rapide

- [Modules principaux](modules.html)
- [Structures de données](annotated.html)
- [Fichiers](files.html)

---

## 🎯 Fonctionnalités principales

1. **Gestion des joueurs** : Initialisation, déplacement et vérification des trésors.
2. **Plateau dynamique** : Création d'un plateau unique pour chaque partie.
3. **Interaction joueur-plateau** : Algorithmes pour résoudre les mouvements et trouver des trésors.

---

## 📦 Structure du projet

Voici une vue d'ensemble des fichiers de votre projet :

| **Fichier**       | **Description**                                  |
|--------------------|--------------------------------------------------|
| `main.c`          | Fichier principal, initialise le programme.      |
| `game.c`          | Gestion de la partie      |
| `joueur.c`        | Gestion des fonctionnalités liées aux joueurs.   |
| `plateau.c`       | Implémente le plateau et ses opérations.         |
| `utils.c`         | Contient des fonctions utilitaires générales.    |

---

## 🚀 Comment jouer

1. Compilez le projet avec le Makefile fourni :
   ```bash
   make
   ```

2. Lancez le programme en ligne de commande :
   ```bash
   ./main
   ```

3. Suivez les instructions affichées pour configurer la partie.

Bon jeu ! 🎲

---

## 🔨 Commande pour le Dev

Compilez le projet avec le Makefile fourni :
   ```bash
   make
   ```

Lancez le programme en ligne de commande :
   ```bash
   ./main
   ```

Compilez avec deubg le projet avec le Makefile fourni :
   ```bash
   make DEBUG=yes
   ```

Compilez Executer les test unitaires du projet avec le Makefile fourni :
   ```bash
   make utest
   ```

Compilez Executer et générer un rapport de couverture de code du projet avec le Makefile fourni :
   ```bash
   make run_test
   ```

Compilez Executer et générer un rapport de leak memory du projet avec le Makefile fourni :
   ```bash
   make valgrind_test
   ```

Mettre à jour la documentation du projet avec le Makefile fourni :
   ```bash
   make docs
   ```

Mettre à jour et lancer la documentation du projet avec le Makefile fourni :
   ```bash
   make run_docs
   ```

Nettoyer les fichiers générer du projet avec le Makefile fourni :
   ```bash
   make clean
   ```

Nettoyer la documentation générer du projet avec le Makefile fourni :
   ```bash
   make clean_docs
   ```

---

### 📋 Pour plus d'informations

- Consultez [les modules et leur documentation](modules.html).
- Explorez les [structures de données utilisées](annotated.html).
- Parcourez [les fichiers et leur contenu](files.html).
*/
