all: GameOfLife

GameOfLife: GameOfLife.cpp
	g++ -std=c++11 GameOfLife.cpp -o GameOfLife
	
clean: 
	rm -rf GameOfLife
