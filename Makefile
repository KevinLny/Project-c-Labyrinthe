# Définition des outils
CC = gcc
CFLAGS = -Wall -MMD
LD = gcc
LDFLAGS = 
LIB = -lcmocka

# Répertoires
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
UNIT_TEST_DIR = unit-test
SDL_DIR = SDL

# Option pour activer/désactiver le mode debug
DEBUG = yes
ifeq ($(DEBUG),yes)
    CFLAGS += -g
endif

# Activer la couverture de code
COVERAGE = yes

ifeq ($(COVERAGE),yes)
    CFLAGS += -fprofile-arcs -ftest-coverage
    LDFLAGS += -fprofile-arcs -ftest-coverage
endif

CFLAGS_SDL = `sdl2-config --cflags`
LIBS_SDL = `sdl2-config --libs` -lSDL2_image -lSDL2_mixer -lSDL2_ttf

# Fichiers sources
MAIN_FILE = $(SRC_DIR)/main.c
SRC_FILES = $(filter-out $(MAIN_FILE), $(wildcard $(SRC_DIR)/*.c))
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))
MAIN_OBJ = $(BUILD_DIR)/main.o

# Fichiers SDL
SDL_SRC = $(wildcard $(SDL_DIR)/*.c)
SDL_OBJ = $(patsubst SDL/%.c, $(BUILD_DIR)/%.o, $(SDL_SRC))

# Fichiers pour les tests
UNIT_TEST_SRC = $(wildcard $(UNIT_TEST_DIR)/*.c)
UNIT_TEST_OBJS = $(patsubst $(UNIT_TEST_DIR)/%.c, $(BUILD_DIR)/%.o, $(UNIT_TEST_SRC))

# Cibles principales
all: main

# Compilation de l'exécutable principal
main: $(OBJ_FILES) $(MAIN_OBJ)
	$(CC) $(LDFLAGS) $^ -o $@ $(LIB)

# Compilation des tests unitaires
utest: $(OBJ_FILES) $(UNIT_TEST_OBJS)
	$(CC) $(LDFLAGS) $^ -o $@ $(LIB)

# Compilation du jeu SDL
sdl: CFLAGS += $(CFLAGS_SDL)
sdl: $(OBJ_FILES) $(SDL_OBJ)
	$(CC) $(CFLAGS) $^ -o sdl $(LIBS_SDL)

# Générer les .o dans le dossier build
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


$(BUILD_DIR)/%.o: SDL/%.c
	$(CC) -c $(CFLAGS) $< -o $@


$(BUILD_DIR)/%.o: $(UNIT_TEST_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Exécuter les tests et générer un rapport de couverture
run_test: utest
	./utest ; \
	lcov --capture --directory . --output-file coverage.info ; \
	genhtml coverage.info --output-directory coverage_report ; \
	valgrind ./utest

# Fuite de mémoire
valgrind_test: utest
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --log-fd=1 ./utest 2>&1 | less -R


# Compilation générique de fichiers objets
%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

# Documentation 
docs:
	doxygen Doxyfile

# Lancer la documentation
run_docs: docs
	xdg-open html/index.html

# Nettoyage
clean:
	rm -f $(BUILD_DIR) *.o main sdl utest *.d *.gcno *.gcda *.gcov *.info -r coverage_report unit-test/*.d unit-test/*.o unit-test/*.gcno unit-test/*.gcda *.txt

clean_docs:
	rm -rf html latex

# Inclusion des dépendances
include $(wildcard *.d)
