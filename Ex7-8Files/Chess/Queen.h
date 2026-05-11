#pragma once
#include "ChessPiece.h"

class Queen : public ChessPiece
{
public:
	Queen(int color, Point pos);
	virtual bool isMoveLegal(const Point& dest, const Board& board) const override;
};