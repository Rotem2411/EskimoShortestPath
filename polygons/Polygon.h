#pragma once

#include "Point2D.h"
#include "Line.h"
#include <vector>

#define MAX_POINTS 15

class Polygon
{
private:

    Point2D m_points[MAX_POINTS];
    int m_NumPoints;

public:
    
    Polygon() : m_NumPoints(0), m_centroid()
    {
        for (int j = 0; j < MAX_POINTS; j++)
            m_points[j].SetPoint();
    }
    Line m_lines[MAX_POINTS];
    Point2D m_centroid;
    int getNumPoints();
    Point2D* getPoint();
    bool addPoint();
    void setPolygon(vertex* v, int dots);
    void setPolygon(Point2D p[], int dots);
    void deletePoint(int CurrInd);
    int convex_hull();
    static Point2D computePolygonCentroid(Point2D* vertices, int vertexCount);
    void extendPolygon(float offset);
};
