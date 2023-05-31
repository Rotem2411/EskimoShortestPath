#pragma once
#include <iostream>
#include <fstream>
#include "Edit_Txt_File.h"
#include "GraphNode.h"
#include "Dubins_Curves.h"

using namespace std;
#define OUTPUT_MATRIX_FILE "matrix_to_matlab.txt"
#define OUTPUT_EXTEND_MATRIX_FILE "extend_matrix_to_matlab.txt"
#define OUTPUT_DIJKSTRA_FILE "DIJKSTRA_path_to_matlab.txt"


void DIJKSTRA(string input_file);