#include "AStar.h"
#include <list>

void printList(list<Node> list, string output_file) {
    ofstream outputFile(output_file);
    Node temp;
    if (outputFile.is_open())
    {
        while (!list.empty()) {
            temp = list.front();
            outputFile << temp.p.getX() << " " << temp.p.getY() << "\n";
            list.pop_front();
        }
        outputFile.close(); // close output file
    }
    else
        cout << "can't create the new file \n";
}

void printList(list<Node*> list, string output_file) {
    ofstream outputFile(output_file);
    Node temp;
    if (outputFile.is_open())
    {
        while (!list.empty()) {
            temp = *list.front();
            outputFile << temp.p.getX() << " " << temp.p.getY() << "\n";
            list.pop_front();
        }
        outputFile.close(); // close output file
    }
    else
        cout << "can't create the new file \n";
}

bool checkObstaclesIntersection(Node start, Node end, Obstacle* Obstacles, int numObstacles)
{
    if (start.m_polygonIdx == end.m_polygonIdx)
        if (abs(start.m_nodeIdx - end.m_nodeIdx) != 1)
            if (abs(start.m_nodeIdx - end.m_nodeIdx) != (Obstacles[start.m_polygonIdx].m_NumNodes - 1))
                return true;
    for (int i = 0; i < numObstacles; i++) {
        if (Obstacle::checkObstacleIntersection(start, end, Obstacles[i].ObstacleEdges, Obstacles[i].m_NumNodes))
            return true;
    }
    return false;
}

void ASTAR(string input_file)
{
    Generator world(input_file);
    world.generateWorld();
    list<Node> closedList{}, openList{};
    closedList.push_back(world.src);
    Node current = world.src;
    while (true) 
    {
        if (current == world.dst)
            break;
        for (int i = 0; i <= world.numNodes; i++)
            if ((world.Nodes[i].inside_polygon==0) && (world.Nodes[i].h < current.h) && //node with lower f than the current node
                (!checkObstaclesIntersection(current, world.Nodes[i], world.o, world.numPolygons))) //not intersect a polygon
            {
                world.Nodes[i].g = world.Nodes[i].g + distance2points(current.p, world.Nodes[i].p);
                world.Nodes[i].f = world.Nodes[i].g + world.Nodes[i].h;
                openList.push_back(world.Nodes[i]);
            }
        openList.sort();
        current = *openList.begin();
        openList.clear();
        closedList.push_back(current);
    }
    printList(closedList, OUTPUT_ASTAR_FILE);
    return;
}
