#include "ChessPiece.h"
#include "Board.h" 
#include <cmath>

ChessPiece::ChessPiece(int color, Point pos, char type)
	: _color(color), _position(pos), _type(type), _hasMoved(false)
{
}

ChessPiece::~ChessPiece() {}
bool ChessPiece::checkStraight(const Point& src, const Point& dest, const Board& board)
{
    int srcX = src.getX();
    int srcY = src.getY();
    int destX = dest.getX();
    int destY = dest.getY();
    bool isHorizontal = (srcY == destY);
    bool isVertical = (srcX == destX);
    if (!isHorizontal && !isVertical)
    {
        return false;
    }
    if (isHorizontal)
    {
        int direction = (destX > srcX) ? 1 : -1;
        for (int x = srcX + direction; x != destX; x += direction)
        {
            if (board.getPiece(Point(x, srcY)) != nullptr)
            {
                return false; 
            }
        }
    }
    else if (isVertical) 
    {
        int direction = (destY > srcY) ? 1 : -1;
        for (int y = srcY + direction; y != destY; y += direction)
        {
            if (board.getPiece(Point(srcX, y)) != nullptr)
            {
                return false; 
            }
        }
    }
    return true;
}

bool ChessPiece::checkDiagonal(const Point& src, const Point& dest, const Board& board)
{
    int srcX = src.getX();
    int srcY = src.getY();
    int destX = dest.getX();
    int destY = dest.getY();
    if (std::abs(destX - srcX) != std::abs(destY - srcY) || std::abs(destX - srcX) == 0)
    {
        return false;
    }
    int x_direction = (destX > srcX) ? 1 : -1;
    int y_direction = (destY > srcY) ? 1 : -1;
    int currentX = srcX + x_direction;
    int currentY = srcY + y_direction;
    while (currentX != destX)
    {
        if (board.getPiece(Point(currentX, currentY)) != nullptr)
        {
            return false;
        }
        currentX += x_direction;
        currentY += y_direction;
    }
    return true;
}

char ChessPiece::getType() const { return _type; }
int ChessPiece::getColor() const { return _color; }
Point ChessPiece::getPosition() const { return _position; }
void ChessPiece::setPosition(Point p) { _position = p; }
void ChessPiece::setMoved() { _hasMoved = true; }
bool ChessPiece::getHasMoved() const { return _hasMoved; }