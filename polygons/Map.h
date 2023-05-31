#pragma once

#include <iostream>
#include "Point2D.h"

class Map
{
public:
    Map() : m_width(0), m_height(0) {}
    Map(int width, int height) : m_width(width), m_height(height) {}

    int width() const { return m_width; }
    int height() const { return m_height; }
    bool isPointInMap(Point2D p) const;

private:

    int m_width;
    int m_height;
};

