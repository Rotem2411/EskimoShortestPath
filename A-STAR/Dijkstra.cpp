#include "Dijkstra.h"


void DIJKSTRA(string input_file)
{
    Generator world(input_file);
    world.generateWorld();
    Graph graph;
    graph.createGraph(world.Nodes, world.numNodes, world.o, world.numPolygons);
    graph.writeMatrixToTxt(OUTPUT_MATRIX_FILE);
    Path path;
    path.DijkstraAlgo(world.src, world.dst, graph);
    path.printPath(world.src, path.m_PathNodes[0]);
    path.writePathToTxt(world.src, path.m_PathNodes[0], OUTPUT_DIJKSTRA_FILE);
    return;
}