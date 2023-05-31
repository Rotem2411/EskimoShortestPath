#include <stdlib.h>
#include "Polygon.h"


int Polygon::getNumPoints() 
{
	return m_NumPoints;
}

Point2D* Polygon::getPoint() 
{ 
	return m_points;
}

bool Polygon::addPoint()
{
	if (m_NumPoints < MAX_POINTS) {
		m_NumPoints++;
		return true;
	}
	else return false;
}

void Polygon::deletePoint(int CurrInd)
{
	m_points[CurrInd].SetPoint();
}

void Polygon::setPolygon(vertex* v, int dots)
{
	m_NumPoints = 0;
	for (int j = 0; j < dots; j++)
	{
		if(addPoint())
			m_points[j].SetPoint(v[j]);
	}
}

void Polygon::setPolygon(Point2D p[], int dots)
{
	m_NumPoints = 0;
	for (int j = 0; j < dots; j++)
	{
		if (addPoint()) {
			m_points[j] = p[j];
		}
	}
	for(int j = 0; j < dots; j++)
		m_lines[j] = Line(m_points[j], m_points[(j + 1)%dots]);
	m_centroid = computePolygonCentroid(p,m_NumPoints);
}

int Polygon::convex_hull()
{
	vertex* v = (vertex*)malloc(m_NumPoints * sizeof(vertex));
	if (v != NULL) {
		for (int j = 0; j < m_NumPoints; j++)
		{
			v[j].x = int(m_points[j].getX() * Multiplyer);
			v[j].y = int(m_points[j].getY() * Multiplyer);
		}
		v = Convex_Hull(v, &m_NumPoints);
		setPolygon(v, m_NumPoints);
		for (int j = 0; j < m_NumPoints; j++)
		{
			m_points[j].setX(float(m_points[j].getX() / Multiplyer));
			m_points[j].setY(float(m_points[j].getY() / Multiplyer));
		}
		for (int j = m_NumPoints; j < MAX_POINTS; j++)
			deletePoint(j);
	}
	free(v);
	return m_NumPoints;
}

Point2D Polygon::computePolygonCentroid(Point2D* vertices, int vertexCount)
{
	Point2D centroid = { 0, 0 };
	float x = 0.0; // centroid X
	float y = 0.0; // centroid Y
	for (int i = 0; i < vertexCount; i++)
	{
		x += vertices[i].getX();
		y += vertices[i].getY();
	}
	centroid.setX( x / vertexCount);
	centroid.setY( y / vertexCount);
	return centroid;
}

void Polygon::extendPolygon(float offset)
{
	float d1,d2,c1,c2;
	int NumPoints = getNumPoints();
	if (offset == 0.0 || NumPoints < 3)
		return ;
	//ax + by + c = 0
	Line lines[MAX_POINTS];
	for (int i = 0; i < NumPoints; i++) {
		lines[i].setA(m_lines[i].getA());
		lines[i].setB(m_lines[i].getB());
		c1 = offset * sqrtf(powf(lines[i].getA(), 2.0f) + powf(lines[i].getB(), 2.0f)) + m_lines[i].getC();
		lines[i].setC(c1);
		d1 = lines[i].DistancePointToLine(m_centroid);
		c2 = m_lines[i].getC() - (offset * sqrtf(powf(lines[i].getA(), 2.0) + powf(lines[i].getB(), 2.0f)));
		lines[i].setC(c2);
		d2 = lines[i].DistancePointToLine(m_centroid);
		if (d1 > d2)
			lines[i].setC(c1);
		else
			lines[i].setC(c2);
	}
	Point2D points_array[MAX_POINTS];

	for (int i = 0; i < NumPoints; i++) {
		points_array[i] = Line::Lineintersection(lines[i], lines[(i+1)%NumPoints]);
	}
	setPolygon(points_array, NumPoints);
	return ;
}
