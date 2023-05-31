#include "Point2D.h"

void Point2D::SetPoint(vertex v) {
    x = (float)v.x;
    y = (float)v.y;
}

void Point2D::SetPoint() {
    x = 0.0;
    y = 0.0;
}

void Point2D::SetPoint(Point2D p)
{
    x = p.x;
    y = p.y;
}