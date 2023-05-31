#include "Map.h"


bool Map::isPointInMap(Point2D p) const {
    if (!(p.getX() >= 0 && p.getX() < m_width && p.getY() >= 0 && p.getY() < m_height)) {
        cout << "point (" << p.getX() << "," << p.getY() << ") is outside the map\n";
        return false;
    }
    return true;
}

