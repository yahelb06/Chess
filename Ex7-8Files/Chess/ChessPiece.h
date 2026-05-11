#pragma once
#include "Point.h"
#include <iostream>

class Board;

class ChessPiece
{
protected:
	Point _position;
	int _color;
	char _type;
	bool _hasMoved;

public:
	ChessPiece(int color, Point pos, char type);
	virtual ~ChessPiece();
	virtual bool isMoveLegal(const Point& dest, const Board& board) const = 0;
	static bool checkStraight(const Point& src, const Point& dest, const Board& board);
	static bool checkDiagonal(const Point& src, const Point& dest, const Board& board);
	char getType() const;
	int getColor() const;
	Point getPosition() const;
	void setPosition(Point p);
	void setMoved();
	bool getHasMoved() const;
};