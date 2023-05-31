#pragma once
#include <iostream>
#include <fstream>
#include "Polygons.h"
#include "Line.h"
#include "Edit_Txt_File.h"
#include <list>
#include <tuple>

using namespace std;

#define MAX_NODES 300
#define INPUT_NUMBERS 650 
#define DATA_TO_MATLAB "data_to_matlab.txt"
#define OUTPUT_FILE "path_to_matlab.txt"
#define OUTPUT_ASTAR_FILE "ASTAR_path_to_matlab.txt"
#define OUTPUT_DIJKSTRA_FILE "DIJKSTRA_path_to_matlab.txt"


float distance2points(Point2D start, Point2D dest);

class Node 
{
private:

public:
    Point2D p;
    float f, g, h; // cost variables for A* algorithm
    Node* next = nullptr;
    Node* prev = nullptr;
    Node* parant = nullptr;
    Node* extend = nullptr;
    bool inside_polygon = false;
    bool flag = false;
    int m_polygonIdx = INT_MAX;
    int m_nodeIdx = INT_MAX;
    Node() : p(), f(0), g(0), h(0) {}
    Node(float a, float b) : p(a,b), f(0), g(0), h(0) {}
    Node(Point2D p, Node end, int polygonIdx) : p(p), g(0), h(distance2points(p, end.p)), f(distance2points(p, end.p)), m_polygonIdx(polygonIdx) {}
    bool operator==(Node& other) { return p.getX() == other.p.getX() && p.getY() == other.p.getY(); }
    bool operator!=(Node& other) { return !(p.getX() == other.p.getX() && p.getY() == other.p.getY()); }
    bool operator<(const Node& other) const { return f < other.f; }
    bool operator>(const Node& other) const { return f > other.f; }
    static float distance2Nodes(Node start, Node dest);
};

class GraphEdge {
public:
    Node start, end;
    float weight;
    GraphEdge() :start(), end(), weight(0) {}
    GraphEdge(Node start, Node end) :start(start), end(end), weight(Node::distance2Nodes(start, end)) {}
};

class Obstacle
{
public:
    int m_NumNodes;
    Node m_nodes[MAX_POINTS];
    GraphEdge ObstacleEdges[MAX_POINTS];
    Obstacle() : m_NumNodes(0) {}
    void createObstacle(Polygon poly);
    static bool checkObstacleIntersection(Node start, Node end, GraphEdge* ObstacleEdges, int numObstacleEdges);
    bool isPointInsidePoly(Node test);
};

class Graph 
{
public:
    Graph()
    {
        memset(matrix, 0, size(matrix));
    }
public:
    int m_numNodes;
    GraphEdge* edge;
    Node m_Nodes[MAX_POINTS * MAX_POLYGONS];
    float matrix[MAX_POINTS* MAX_POLYGONS][MAX_POINTS* MAX_POLYGONS];
    void createGraph(Node* node, int numNodes, Obstacle* o, int numObstacles);
    void createMatrix(Obstacle* o, int numObstacles);
    void writeMatrixToTxt(string output_file);
    static bool checkObstaclesIntersection(Node start, Node end, Obstacle* Obstacles, int numObstacles);
    static bool Lineintersection(Point2D A, Point2D B, Point2D C, Point2D D);
};

class Path {
public:

    Node m_PathNodes[MAX_POINTS * MAX_POLYGONS];
    int m_PathNumNodes=0;
    void printPath(Node start, Node goal);
    int miniDist(float distance[], bool Tset[], int NumNodes);
    void DijkstraAlgo(Node start, Node goal, Graph graph);
    void writePathToTxt(Node start, Node goal, string output_file);
};

class Generator 
{
public:
    Obstacle *o;
    Node src, dst, Nodes[MAX_POLYGONS * MAX_POINTS];
    int numPolygons, numNodes;
    float numbersArr[INPUT_NUMBERS];
    Polygons stPolygons;

    Generator(): src(), dst(), Nodes(), o(), numPolygons() {}
    Generator(string input_file) {
        read_txt_file(input_file);
    }
    bool read_txt_file(string input_file);
    void create_txt_file(Map map, Point2D src, Point2D dst, int NumPolygons, string output_file);
    void write_txt_file(Polygon p, string output_file);
    void generateWorld();
    bool pyTxt2Cpp(string input_file);
};
