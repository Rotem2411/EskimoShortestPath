#pragma once

#include <iostream>
#include <fstream>
#include "Edit_Txt_File.h"
#include "GraphNode.h"
#include "Dubins_Curves.h"


using namespace std;
#define OUTPUT_MATRIX_FILE "matrix_to_matlab.txt"
#define OUTPUT_EXTEND_MATRIX_FILE "extend_matrix_to_matlab.txt"

void writeDubinsPathToTxt(string output_file, float q[2]);

int printASTARConfiguration(float q[3], float x, void* user_data);

int printDIJKSTRAConfiguration(float q[3], float x, void* user_data);

void DIJKSTRA_DUBINS(string input_file);

void ASTAR_DUBINS(string input_file);