cmake_minimum_required(VERSION 2.6)

project(othello)
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -O3")

add_executable(battle.out battle.cpp game.cpp functions.cpp player.cpp learner.cpp man.cpp aho.cpp alphabeta.cpp primitivemc.cpp mcts.cpp td.cpp network.cpp)
add_executable(training.out functions.cpp trainer.cpp training.cpp player.cpp learner.cpp td.cpp network.cpp)
add_executable(check.out check.cpp functions.cpp player.cpp learner.cpp td.cpp network.cpp)
