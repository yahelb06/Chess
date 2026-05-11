#pragma once
#include "ChessPiece.h"
#include "Board.h" 

class Rook : public ChessPiece
{
public:
	Rook(int color, Point pos);
	virtual bool isMoveLegal(const Point& dest, const Board& board) const override;
};