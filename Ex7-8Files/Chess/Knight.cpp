#include "Knight.h"

Knight::Knight(int color, Point pos) : ChessPiece(color, pos, (color == 0 ? 'N' : 'n'))
{
}

bool Knight::isMoveLegal(const Point& dest, const Board& board) const
{
	int srcX = _position.getX();
	int srcY = _position.getY();
	int destX = dest.getX();
	int destY = dest.getY();
	int move_x = abs(destX - srcX);
	int move_y = abs(destY - srcY);
	if(move_x == 0 || move_y == 0)
	{
		return false;
	}
	else if(move_x == 1 && move_y == 2)
	{
		return true;
	}
	else if(move_x == 2 && move_y == 1)
	{
		return true;
	}
	return false;
}