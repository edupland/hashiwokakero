#Version minimale requise
cmake_minimum_required(VERSION 2.6)

#Nom du projet
project(hashi_text C)

#On définit le répertoire d'installation comme étant le répertoire courant
set(CMAKE_INSTALL_PREFIX .)

#Permet de spécifier l'ajout de "-I" à la compilation
include_directories(../include)

#On définit les CFLAGS
set(CMAKE_C_FLAGS "-std=c99 -g -Wall")

#On crée la librairie libhashi.a
add_library(hashi node.c game.c)

#Création de l'exécutable hashi_text puis link de libhashi
add_executable(hashi_text hashi_text.c grid_update.c init_game.c user_interac.c)
target_link_libraries(hashi_text m hashi)

#Solveur
add_executable(hashi_solve hashi_solve.c init_game)
target_link_libraries(hashi_solve hashi m)

#Création des exécutables de test
add_executable(test_game1 test_game1.c test_toolbox.c)
target_link_libraries(test_game1 hashi m)

add_executable(test_game2 test_game2.c test_toolbox.c)
target_link_libraries(test_game2 hashi m)

add_executable(test_game3 test_game3.c test_toolbox.c)
target_link_libraries(test_game3 hashi m)

add_executable(test_game4 test_game4.c test_toolbox.c)
target_link_libraries(test_game4 hashi m)

#On définit des répertoires d'installation pour nos exécutables et notre librairie
install(TARGETS hashi_text test_game1 test_game2 test_game3 test_game4 hashi RUNTIME DESTINATION bin
		ARCHIVE DESTINATION lib
		LIBRARY DESTINATION lib)

install(TARGETS hashi_solve RUNTIME DESTINATION .)

#Simple copie de la grille du jeu vers le répertoire contenant l'exécutable
install(FILES game_default.txt game_easy.txt game_medium.txt DESTINATION bin)
