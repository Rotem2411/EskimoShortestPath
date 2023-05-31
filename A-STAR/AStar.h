#pragma once

#include <iostream>
#include <fstream>
#include "Edit_Txt_File.h"
#include "GraphNode.h"

using namespace std;
#define OUTPUT_MATRIX_FILE "matrix_to_matlab.txt"
#define OUTPUT_EXTEND_MATRIX_FILE "extend_matrix_to_matlab.txt"
#define OUTPUT_ASTAR_FILE "ASTAR_path_to_matlab.txt"

void printList(list<Node> list, string output_file);
void printList(list<Node*> list, string output_file);
bool checkObstaclesIntersection(Node start, Node end, Obstacle* Obstacles, int numObstacles);
void ASTAR(string input_file);