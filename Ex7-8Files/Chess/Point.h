#pragma once

class Point
{
private:
	int _x;
	int _y; 
public:
	Point(int x = 0, int y = 0) : _x(x), _y(y) {}
	int getX() const { return _x; }
	int getY() const { return _y; }
	bool operator==(const Point& other) const 
	{
		return _x == other._x && _y == other._y;
	}
};
