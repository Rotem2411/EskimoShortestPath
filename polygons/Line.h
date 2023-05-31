#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <math.h>
#include "Point2D.h"


#define EPSILON 0.001

using namespace std;


/*
ax + by + c = (py – qy)x + (qx – px)y + (pxqy – qxpy) = 0
*/

class Line {
private:
    float a, b, c;
public:
    Line(): a(0), b(0), c(0) {}
    Line(vertex Q, vertex P);
    Line(Point2D Q, Point2D P);

    float getA();
    float getB();
    float getC();
    void setA(float a);
    void setB(float b);
    void setC(float c);

    void printLine();

    static Point2D Lineintersection(Point2D A, Point2D B, Point2D C, Point2D D);

    // A Function to calculate the distance between 2 points.
    float distance2points(Point2D start, Point2D dest);

    static Point2D Lineintersection(Line A, Line B);

    float DistancePointToLine(Point2D point);

};