#include "Rook.h"

Rook::Rook(int color, Point pos)
	: ChessPiece(color, pos, (color == 0 ? 'R' : 'r'))
{
}

bool Rook::isMoveLegal(const Point& dest, const Board& board) const
{
	return ChessPiece::checkStraight(_position, dest, board);
}