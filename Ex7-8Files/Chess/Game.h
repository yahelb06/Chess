#pragma once
#include "Board.h"
#include <string>

class Game
{
private:
	Board _board; 
	Point parseMoveString(std::string move);

public:
	Game();
	std::string handleMove(std::string moveStr);
	std::string getBoardState() const;
	void printCurrentBoard() const;
};