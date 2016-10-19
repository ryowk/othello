cmake_minimum_required(VERSION 2.6)

project(othello CXX)
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -O3")

include_directories("./include")

add_library(functions STATIC functions.cpp)
add_library(players STATIC player.cpp learner.cpp man.cpp aho.cpp alphabeta.cpp primitivemc.cpp mcts.cpp td.cpp network.cpp)
add_library(game game.cpp)

add_executable(battle.out battle.cpp)
target_link_libraries(battle.out functions players game)

add_executable(training.out trainer.cpp training.cpp)
target_link_libraries(training.out functions players game)

add_executable(check.out check.cpp)
target_link_libraries(check.out functions players)
