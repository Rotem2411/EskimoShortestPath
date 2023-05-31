#pragma once
#include <iostream>
#include <fstream>
#include "Convex_Hull.h"

using namespace std;

class Point2D
{
private:
    float x, y;

public:
    Point2D() : x(), y() {}
    Point2D(float x, float y) : x(x), y(y) {}
    void SetPoint(vertex v);
    void SetPoint();
    void SetPoint(Point2D p);
    float getX() { return x; }
    float getY() { return y; }
    void setX(float X) { x=X; }
    void setY(float Y) { y=Y; }
    bool operator ==(const Point2D& p) const { return p.x == x && p.y == y; }
    bool operator !=(Point2D& p) { return !(p.x == x && p.y == y); }
    void display() {
        cout << "(" << getX() << ", " << getY() << ")";
    }
};