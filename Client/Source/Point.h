#pragma once
class Point
{
public:

	Point() : x(0), y(0) { }
	Point(int x, int y) : x(x), y(y) { }

	int getX() const { return x; }
	int getY() const { return y; }

	int setX(int newX) { return x = newX; }
	int setY(int newY) { return y = newY; }

	int setPosition(int newX, int newY) { return x = newX, y = newY; }
private:
	int x, y;
};

