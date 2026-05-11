#pragma once
#include "ChessPiece.h"

class King : public ChessPiece
{
public:
	King(int color, Point pos);
	virtual bool isMoveLegal(const Point& dest, const Board& board) const override;
};