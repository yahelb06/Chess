#include "Pawn.h"
#include "Board.h"
#include <cmath>

Pawn::Pawn(int color, Point pos)
	: ChessPiece(color, pos, (color == 0 ? 'P' : 'p'))
{
}

bool Pawn::isMoveLegal(const Point& dest, const Board& board) const
{
	int srcX = _position.getX();
	int srcY = _position.getY();
	int destX = dest.getX();
	int destY = dest.getY();
	int direction = (_color == 0) ? 1 : -1;
	int dx = std::abs(destX - srcX);
	int dy = destY - srcY;
	if (dx == 0)
	{
		if (dy == direction)
		{
			if (board.getPiece(dest) == nullptr)
			{
				return true;
			}
		}
		else if (dy == 2 * direction)
		{
			if (!_hasMoved)
			{
				Point middle(srcX, srcY + direction);
				if (board.getPiece(dest) == nullptr && board.getPiece(middle) == nullptr)
				{
					return true;
				}
			}
		}
	}
	else if (dx == 1)
	{
		if (dy == direction)
		{
			if (board.getPiece(dest) != nullptr)
			{
				return true;
			}
		}
	}

	return false;
}