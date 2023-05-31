#include "Dubins.h"
#include "AStar.h"
#include "Dubins_Curves.h"
#include <algorithm>

#define OUTPUT_FILE_NEWPOLYGON "newpolygon_to_matlab.txt"
#define EXTEND 10.0
using namespace DubinsCurves;

void writeDubinsPathToTxt(string output_file, float q[2])
{
    ofstream outputFile(output_file, std::ofstream::app);
    if (outputFile.is_open())
    {
        outputFile << q[0] << ' ' << q[1] << "\n";
    }
    else
        cout << "can't create the new file \n";
}

int printASTARConfiguration(float q[3], float x, void* user_data) {
    writeDubinsPathToTxt(OUTPUT_FILE_ASTAR_DUBINS, q);
    return 0;
}

int printDIJKSTRAConfiguration(float q[3], float x, void* user_data) {
    writeDubinsPathToTxt(OUTPUT_FILE_DIJKSTRA_DUBINS, q);
    return 0;
}

void DIJKSTRA_DUBINS(string input_file)
{
    Generator world(input_file);
    world.generateWorld();

    for (int j = 0; j < world.numPolygons; j++)
        world.stPolygons.getPolygons()[j].extendPolygon(EXTEND);
    for (int j = 0; j < world.numPolygons; j++)
        world.o[j].createObstacle(world.stPolygons.getPolygons()[j]);
    for (int j = 0; j < world.numPolygons; j++) {
        world.write_txt_file(world.stPolygons.getPolygons()[j], OUTPUT_FILE_NEWPOLYGON);
    }

    for (int j = 0, n = 1; j < world.numPolygons; j++)
        for (int i = 0; i < world.stPolygons.getPolygons()[j].getNumPoints(); i++, n++)
        {
            world.Nodes[n].p = world.stPolygons.getPolygons()[j].getPoint()[i];
        }

    Graph graph;
    graph.createGraph(world.Nodes, world.numNodes, world.o, world.numPolygons);
    graph.writeMatrixToTxt(OUTPUT_EXTEND_MATRIX_FILE);
    Path path;
    path.DijkstraAlgo(world.src, world.dst, graph);
    DubinsPath dubinsPath;
    ofstream outputFile(OUTPUT_FILE_DIJKSTRA_DUBINS);
    float radius = EXTEND;
    for (int i = path.m_PathNumNodes - 1; i > 0; i--) {
        float q0[] = { path.m_PathNodes[i].p.getX(), path.m_PathNodes[i].p.getY(), 0 };
        float q1[] = { path.m_PathNodes[i - 1].p.getX(), path.m_PathNodes[i - 1].p.getY(), 0 };
        dubins_init(q0, q1, radius, &dubinsPath);
        dubins_path_sample_many(&dubinsPath, printDIJKSTRAConfiguration, 0.5, NULL);
    }
    outputFile.close(); // close output file
    delete world.o;
    return;
}

void ASTAR_DUBINS(string input_file) 
{
    Generator world(input_file);
    world.generateWorld();

    for (int j = 0; j < world.numPolygons; j++)
        world.stPolygons.getPolygons()[j].extendPolygon(EXTEND);
    for (int j = 0; j < world.numPolygons; j++)
        world.o[j].createObstacle(world.stPolygons.getPolygons()[j]);
    for (int j = 0; j < world.numPolygons; j++) 
        world.write_txt_file(world.stPolygons.getPolygons()[j], OUTPUT_FILE_NEWPOLYGON);

    for (int j = 0, n = 1; j < world.numPolygons; j++)
        for (int i = 0; i < world.stPolygons.getPolygons()[j].getNumPoints(); i++, n++) {
            world.Nodes[n].p = world.stPolygons.getPolygons()[j].getPoint()[i];
            world.Nodes[n].h = Node::distance2Nodes(world.Nodes[n], world.dst);
            world.Nodes[n].f = world.Nodes[n].h;
        }

    for (int i = 0; i <= world.numNodes; i++)
        for (int k = 0; k < world.numPolygons; k++)
            if (world.o[k].isPointInsidePoly(world.Nodes[i]) && world.Nodes[i].m_polygonIdx != k) //not intersect a polygon
                world.Nodes[i].inside_polygon = true;

    list<Node*> closedList{}, openList{};
    closedList.push_back(&world.src);
    Node* current = &world.src;
    while (true) 
    {
        if (*current == world.dst)
            break;
        for (int i = 0; i <= world.numNodes; i++)
            if ((world.Nodes[i].inside_polygon==false) //node not inside other polygon
                && (world.Nodes[i].flag == false) //node hasn't further nodes in direction to destination
                && (world.Nodes[i].h < current->h) //node with lower f than the current node
                && (!checkObstaclesIntersection(*current, world.Nodes[i], world.o, world.numPolygons))) //not intersect a polygon
                {
                    world.Nodes[i].g = world.Nodes[i].g + distance2points(current->p, world.Nodes[i].p);
                    world.Nodes[i].f = world.Nodes[i].g + world.Nodes[i].h;
                    openList.push_back(&world.Nodes[i]);
                }
        if (openList.empty())
        {
            current->flag = true; //node has no further nodes in direction to destination
            closedList.pop_back();
            current = closedList.back();
            continue;
        }
        openList.sort([](Node* a, Node* b) {return (a->f) < (b->f); });
        current = openList.front();
        openList.clear();
        closedList.push_back(current);
    }

    DubinsPath dubinsPath;
    ofstream outputFile(OUTPUT_FILE_ASTAR_DUBINS);
    float radius = EXTEND;
    while (*closedList.front() != world.dst)
    {
        Node temp = *closedList.front();
        closedList.pop_front();
        Node temp1 = *closedList.front();
        float q0[] = { temp.p.getX(), temp.p.getY(), 0 };
        float q1[] = { temp1.p.getX(), temp1.p.getY(), 0 };
        dubins_init(q0, q1, radius, &dubinsPath);
        dubins_path_sample_many(&dubinsPath, printASTARConfiguration, 0.5, NULL);
    }

    outputFile.close(); // close output file
    return;
}
    
