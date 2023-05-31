#include "Polygons.h"


bool Polygons::addPolygon(Point2D points[], int dots)
{
	if (m_NumPolygons < MAX_POLYGONS) {
		polygons_arry[m_NumPolygons++].setPolygon(points, dots);
		return true;
	}
	return false;
}

Polygon* Polygons::getPolygons()
{
	return polygons_arry;
}

//Polygon Polygons::getPolygon(int i)
//{
//	return polygons_arry[i];
//}
