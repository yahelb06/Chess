#include "Game.h"
#include <iostream>

Game::Game()
{
}

std::string Game::getBoardState() const
{
	return _board.getBoardStateString();
}

std::string Game::handleMove(std::string moveStr)
{
	if (moveStr.length() != 4)
	{
		return "5"; 
	}
	std::string sourceStr = moveStr.substr(0, 2); 
	std::string destStr = moveStr.substr(2, 2);   
	Point src = parseMoveString(sourceStr);
	Point dest = parseMoveString(destStr);
	int resultCode = _board.tryMove(src, dest);
	std::string response = std::to_string(resultCode);

	return response;
}

Point Game::parseMoveString(std::string move)
{
	int col = move[0] - 'a';
	int row = '8' - move[1];
	return Point(col, row);
}

void Game::printCurrentBoard() const
{
	_board.printBoard();
}