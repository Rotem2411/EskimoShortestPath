#pragma once
#include <iostream>
#include <fstream>
#include "Edit_Txt_File.h"
#include "GraphNode.h"


using namespace std;

#define INPUT_CPP_FILE "data_to_cpp.txt"
#define DATA_TO_MATLAB "data_to_matlab.txt"

bool pyTxt2Cpp(string input_file);

