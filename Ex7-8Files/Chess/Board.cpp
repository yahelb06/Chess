#include "Board.h"
#include "Rook.h"
#include "Bishop.h"
#include "Pawn.h"
#include "Knight.h"
#include "King.h"
#include "Queen.h"
#include <iostream>
#include <string>

//crates a full board with correct places
Board::Board() : _turn(1) 
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			_board[i][j] = nullptr;
		}
	}
	_board[0][0] = new Rook(0, Point(0, 0));
	_board[0][1] = new Knight(0, Point(1, 0));
	_board[0][2] = new Bishop(0, Point(2, 0));
	_board[0][3] = new Queen(0, Point(3, 0));
	_board[0][4] = new King(0, Point(4, 0));
	_board[0][5] = new Bishop(0, Point(5, 0));
	_board[0][6] = new Knight(0, Point(6, 0));
	_board[0][7] = new Rook(0, Point(7, 0));
	//White Pawns
	for (int i = 0; i < 8; i++)
	{
		_board[1][i] = new Pawn(0, Point(i, 1));
	}
	//Black Pawns
	for (int i = 0; i < 8; i++)
	{
		_board[6][i] = new Pawn(1, Point(i, 6));
	}
	//black Pieces
	_board[7][0] = new Rook(1, Point(0, 7));
	_board[7][1] = new Knight(1, Point(1, 7));
	_board[7][2] = new Bishop(1, Point(2, 7));
	_board[7][3] = new Queen(1, Point(3, 7));
	_board[7][4] = new King(1, Point(4, 7));
	_board[7][5] = new Bishop(1, Point(5, 7));
	_board[7][6] = new Knight(1, Point(6, 7));
	_board[7][7] = new Rook(1, Point(7, 7));
}

//delBoard
Board::~Board()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (_board[i][j] != nullptr)
			{
				delete _board[i][j];
			}
		}
	}
}


ChessPiece* Board::getPiece(Point p) const
{
	if (p.getX() < 0 || p.getX() >= 8 || p.getY() < 0 || p.getY() >= 8)
	{
		return nullptr;
	}
	return _board[p.getY()][p.getX()];
}

void Board::turnSwitch() { _turn = 1 - _turn; }
int Board::getTurn() const { return _turn; }

std::string Board::getBoardStateString() const
{
	std::string res = "";
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (_board[i][j] == nullptr)
				res += "#";
			else
				res += _board[i][j]->getType();
		}
	}
	res += (_turn == 0 ? "0" : "1");
	return res;
}

void Board::printBoard() const
{
	for (int y = 0; y < 8; ++y)
	{
		for (int x = 0; x < 8; ++x)
		{
			ChessPiece* piece = _board[y][x];
			char pieceChar = (piece == nullptr) ? '#' : piece->getType();
			std::cout << pieceChar << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "Turn: " << (_turn == 0 ? "White" : "Black") << std::endl;
}

Point Board::findKing(int color) const
{
	char kingType = (color == 0 ? 'K' : 'k'); // K White, k Black
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (_board[i][j] != nullptr && _board[i][j]->getType() == kingType)
			{
				return _board[i][j]->getPosition();
			}
		}
	}
	return Point(-1, -1);//if Bug somewhere
}

bool Board::isUnderAttack(Point p, int attackerColor) const
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			ChessPiece* piece = _board[i][j];
			if (piece != nullptr && piece->getColor() == attackerColor)
			{
				if (piece->isMoveLegal(p, *this))
				{
					return true;
				}
			}
		}
	}
	return false;
}

//check 8 - is it CHECKMATE 
//gets the color of ur king and checks every possible check to ensure it is an impossiblw to defend check
bool Board::isCheckMate(int kingColor)
{
	int attackerColor = 1 - kingColor;
	Point currentKingPos = findKing(kingColor);
	if (!isUnderAttack(currentKingPos, attackerColor))
	{
		return false;
	}

	for (int srcRow = 0; srcRow < 8; srcRow++)
	{
		for (int srcCol = 0; srcCol < 8; srcCol++)
		{
			Point src(srcCol, srcRow);
			ChessPiece* srcPiece = getPiece(src);

			if (srcPiece != nullptr && srcPiece->getColor() == kingColor)
			{
				for (int destRow = 0; destRow < 8; destRow++)
				{
					for (int destCol = 0; destCol < 8; destCol++)
					{
						Point dest(destCol, destRow);
						ChessPiece* destPiece = getPiece(dest);
						if (src == dest ||(destPiece != nullptr && destPiece->getColor() == kingColor) ||!srcPiece->isMoveLegal(dest, *this))
						{
							continue;
						}
						ChessPiece* tempDestPiece = _board[dest.getY()][dest.getX()];
						Point oldPos = srcPiece->getPosition();
						_board[dest.getY()][dest.getX()] = srcPiece;
						_board[src.getY()][src.getX()] = nullptr;
						srcPiece->setPosition(dest);
						Point kingPosAfterMove = (srcPiece->getType() == 'K' || srcPiece->getType() == 'k') ? dest : currentKingPos;
						bool stillInCheck = isUnderAttack(kingPosAfterMove, attackerColor);
						srcPiece->setPosition(oldPos);
						_board[src.getY()][src.getX()] = srcPiece;
						_board[dest.getY()][dest.getX()] = tempDestPiece;
						if (!stillInCheck)
						{
							return false; // there is a save move
						}
					}
				}
			}
		}
	}
	return true; //no move can save you - MATE
}


//func gets src and dst points and checks every possible option accronding to the matzeget in a smart order
int Board::tryMove(Point src, Point dest)
{
	// Check 5:
	if (src.getX() < 0 || src.getX() > 7 || src.getY() < 0 || src.getY() > 7 || dest.getX() < 0 || dest.getX() > 7 || dest.getY() < 0 || dest.getY() > 7)
	{
		return 5;
	}
	// Check 7:
	if (src == dest)
	{
		return 7;
	}
	ChessPiece* srcPiece = getPiece(src);
	ChessPiece* destPiece = getPiece(dest);
	// Check 2:
	if (srcPiece == nullptr || srcPiece->getColor() != _turn)
	{
		return 2;
	}
	// Check 3:
	if (destPiece != nullptr && destPiece->getColor() == _turn)
	{
		return 3;
	}
	// Check 6:
	if (!srcPiece->isMoveLegal(dest, *this))
	{
		return 6;
	}

	// Check 4:
	ChessPiece* tempDestPiece = _board[dest.getY()][dest.getX()];
	Point oldPos = srcPiece->getPosition();
	_board[dest.getY()][dest.getX()] = srcPiece;	
	_board[src.getY()][src.getX()] = nullptr;
	srcPiece->setPosition(dest);
	int myKingColor = _turn;
	Point myKingPos = findKing(myKingColor);
	bool selfCheck = isUnderAttack(myKingPos, 1 - _turn);
	srcPiece->setPosition(oldPos);
	_board[src.getY()][src.getX()] = srcPiece;
	_board[dest.getY()][dest.getX()] = tempDestPiece;

	if (selfCheck)
	{
		return 4;
	}

	// Real Move (Commit)
	if (destPiece != nullptr)
	{
		delete destPiece;//if eating a piece
	}
	_board[dest.getY()][dest.getX()] = srcPiece;
	_board[src.getY()][src.getX()] = nullptr;
	srcPiece->setPosition(dest);
	srcPiece->setMoved();
	//Check 1 & 8
	int opponentColor = 1 - _turn;
	Point opponentKingPos = findKing(opponentColor);
	if (isUnderAttack(opponentKingPos, _turn))
	{
		if (isCheckMate(opponentColor))
		{
			turnSwitch();
			return 1;//return 8; bc mate changed to ret 1 for autochecks
		}

		turnSwitch();
		return 1; //Check
	}
	turnSwitch();
	return 0;//Ok move
}