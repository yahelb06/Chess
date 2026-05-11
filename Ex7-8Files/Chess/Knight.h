#pragma once
#include "Board.h"
#include "ChessPiece.h"

class Knight : public ChessPiece
{
public:
	Knight(int color, Point pos);
	virtual bool isMoveLegal(const Point& dest, const Board& board) const override;
};