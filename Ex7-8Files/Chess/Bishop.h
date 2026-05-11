#pragma once
#include "ChessPiece.h"
#include "Board.h"

class Bishop : public ChessPiece
{
public:
	Bishop(int color, Point pos);
	virtual bool isMoveLegal(const Point& dest, const Board& board) const override;
};