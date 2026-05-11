#pragma once
#include "ChessPiece.h"
#include <string>
#define BOARD_SIZE 8

class Board
{
private:
	ChessPiece* _board[BOARD_SIZE][BOARD_SIZE];
	int _turn; 

public:
	Board();
	~Board();
	ChessPiece* getPiece(Point p) const;
	void turnSwitch();
	int getTurn() const;
	int tryMove(Point src, Point dest);
	std::string getBoardStateString() const;
	void printBoard() const;
	Point findKing(int color) const; 
	bool isUnderAttack(Point p, int attackerColor) const; 
	bool isCheckMate(int kingColor); 
};