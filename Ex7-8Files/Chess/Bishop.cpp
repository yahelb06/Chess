#include "Bishop.h"

Bishop::Bishop(int color, Point pos)
	: ChessPiece(color, pos, (color == 0 ? 'B' : 'b'))
{
}

bool Bishop::isMoveLegal(const Point& dest, const Board& board) const
{
	return ChessPiece::checkDiagonal(_position, dest, board);
}