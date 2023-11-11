#!/bin/bash

g++ -g grid.cpp entity.cpp plate.cpp game.cpp pitcher.cpp cannon.cpp rocket.cpp main.cpp -I$(pwd)/include -lpthread -o iron_dome_game 
