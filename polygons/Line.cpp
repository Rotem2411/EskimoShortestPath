#include "Line.h"


Line::Line(vertex Q, vertex P) {
    a = float((P.y / Multiplyer) - (Q.y / Multiplyer));
    b = float((Q.x / Multiplyer) - (P.x / Multiplyer));
    c = float((Q.y / Multiplyer) * (P.x / Multiplyer) - (Q.x / Multiplyer) * (P.y / Multiplyer));
}

Line::Line(Point2D Q, Point2D P) {
    a = P.getY() - Q.getY();
    b = Q.getX() - P.getX();
    c = Q.getY() * P.getX() - Q.getX() * P.getY();
}

float Line::getA()
{
    return this->a;
}

float Line::getB()
{
    return this->b;
}

float Line::getC()
{
    return this->c;
}

void Line::setA(float a)
{
    this->a = a;
}

void Line::setB(float b)
{
    this->b = b;
}

void Line::setC(float c)
{
    this->c = c;
}


void Line::printLine() {
    if (b < 0)
        cout << "The line is :" << a << "x - " << abs(b) << "y = " << -c << "\n";
    else
        cout << "The line is: " << a << "x + " << b << "y = " << -c << "\n";
}

Point2D Line::Lineintersection(Point2D A1, Point2D A2, Point2D B1, Point2D B2)
{
    Point2D ReturnedVal(FLT_MAX, FLT_MAX);
    // Line A represented as a1x + b1y = c1
    float a1 = A2.getY() - A1.getY();
    float b1 = A1.getX() - A2.getX();
    float c1 = a1 * (A1.getX()) + b1 * (A1.getY());
    // Line B represented as a2x + b2y = c2
    float a2 = B2.getY() - B1.getY();
    float b2 = B1.getX() - B2.getX();
    float c2 = a2 * (B1.getX()) + b2 * (B1.getY());
    float det = a1 * b2 - a2 * b1;
    if (abs(det) > EPSILON) {
        float x = (b2 * c1 - b1 * c2) / det;
        float y = (a1 * c2 - a2 * c1) / det;
        if (x == -0.0) 
            x = 0;
        if (y == -0.0) 
            y = 0;
        if ((x > min(A1.getX(), A2.getX()) && x < max(A1.getX(), A2.getX())) && (y > min(A1.getY(), A2.getY()) && y < max(A1.getY(), A2.getY())) &&
            (x > min(B1.getX(), B2.getX()) && x < max(B1.getX(), B2.getX())) && (y > min(B1.getY(), B2.getY()) && y < max(B1.getY(), B2.getY())))
            ReturnedVal = Point2D(x, y);
    }
    return ReturnedVal;
}

float Line::distance2points(Point2D start, Point2D dest)
{
    return (sqrtf(powf(dest.getX() - start.getX(), 2.0f) + powf(dest.getY() - start.getY(), 2.0f)));
}

Point2D Line::Lineintersection(Line AB, Line CD)
{
    Point2D ReturnedVal(FLT_MAX, FLT_MAX);
    float det = AB.a * CD.b - CD.a * AB.b;
    if (abs(det) > EPSILON) { 
        float x = (AB.b * CD.c - CD.b * AB.c) / det;
        float y = (CD.a * AB.c - AB.a * CD.c) / det;
        ReturnedVal = Point2D(x, y);
    }
    return ReturnedVal;
}

float Line::DistancePointToLine(Point2D point)
{
    return abs(a * point.getX() + b * point.getY() + c) / sqrt(a * a + b * b);
}
