#include "Queen.h"

Queen::Queen(int color, Point pos)
	: ChessPiece(color, pos, (color == 0 ? 'Q' : 'q'))
{
}

bool Queen::isMoveLegal(const Point& dest, const Board& board) const
{
	bool straightMove = ChessPiece::checkStraight(_position, dest, board);
	bool diagonalMove = ChessPiece::checkDiagonal(_position, dest, board);
	return straightMove || diagonalMove;
}