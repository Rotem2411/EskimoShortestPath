#pragma once
#include <iostream>
#include <fstream>
#include "Polygon.h"


using namespace std;

#define MAX_POLYGONS 20

class Polygons
{
private:

    int m_NumPolygons;
    Polygon polygons_arry[MAX_POLYGONS];

public:

    Polygons()
    {
        m_NumPolygons = 0;
    }
    bool addPolygon(Point2D points[], int dots);
    Polygon* getPolygons();
    //Polygon getPolygon(int i);
    int getNumOfPolygons() { return m_NumPolygons; }
};