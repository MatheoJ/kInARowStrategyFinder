# Definition des variables necessaires au Makefile

# Compilateur
CC = g++

# Flags de compilation mettre -std=c++2a si on veut utiliser c++20
CFLAGS = -g -ansi -pedantic -Wall -std=c++2a -pthread

# Repertoire des fichiers sources
SRC = ./src

# Repertoire des fichiers assemblés
OBJ = ./build

# Recuperation de tous les fichiers .h et .cpp
# du dossier des sources grâce à la fonction wildcard
SRCS = $(wildcard $(SRC)/*.cpp)

# Creation des .o à partir des .cpp en utilisant un pattern de substitution
OBJS = $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRCS))

# Repertoire et Nom pour l'exécutable
DISTDIR = dist
EXENAME = prog
GUIINCLUDE =

# Regroupement du Repertoire et du Nom de l'exécutable
# dans une seule variable pour plus de commodité
DIST = $(DISTDIR)/$(EXENAME)


# Creation de l'exécutable en mode console
all: SRCS := $(filter-out %mainGUI.cpp, $(SRCS))
all: initobj initdist clean
all: $(DIST)

# Creation de l'exécutable en mode gui
gui: SRCS := $(filter-out %main.cpp, $(SRCS))
gui: initobj initdist clean
gui: GUIINCLUDE := -lsfml-graphics -lsfml-window -lsfml-system
gui: EXENAME := progGUI
gui: DIST:= $(DISTDIR)/$(EXENAME)
gui: $(DIST)


# Creation de l'exécutable en mode Debug
release: CFLAGS = -g -ansi -pedantic -Wall -std=c++11 -D MAP
release: clean
release: $(DIST)

# Commande d'édition des liens
$(DIST): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(DIST) $(GUIINCLUDE)

# Commande d'assemblage (réalise également le traitement par le préprocesseur et la compilation)
$(OBJ)/%.o : $(SRC)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@ 

# Commande de nettoyage (destruction de l'exécutable et des fichiers assemblés)
clean:
	$(RM) -r $(DIST) $(OBJ)/*

# Commande d'initialisation du projet
init : initobj initsrc

initobj :
	if [ ! -d "$(OBJ)" ]; then\
		echo "Creating objects directory";\
		mkdir $(OBJ);\
	fi

initdist :
	if [ ! -d "$(DISTDIR)" ]; then\
		echo "Creating dist directory";\
		mkdir $(DISTDIR);\
	fi

initsrc :
	if [ ! -d "$(SRC)" ]; then\
		echo "Creating source directory";\
		mkdir $(SRC);\
	fi
