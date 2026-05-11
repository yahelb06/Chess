#include "King.h"
#include "Board.h" 
#include <cmath>

King::King(int color, Point pos): ChessPiece(color, pos, (color == 0 ? 'K' : 'k')) 
{
}

bool King::isMoveLegal(const Point& dest, const Board& board) const
{
	int dx = std::abs(dest.getX() - _position.getX());
	int dy = std::abs(dest.getY() - _position.getY());
	if (dx <= 1 && dy <= 1) 
	{
		return true;
	}
	return false;
}