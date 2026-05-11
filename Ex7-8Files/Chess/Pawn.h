#pragma once
#include "ChessPiece.h"

class Pawn : public ChessPiece
{
public:
	Pawn(int color, Point pos);
	virtual bool isMoveLegal(const Point& dest, const Board& board) const override;
};