#include "PythonTxt2Cpp.h"
#include "AStar.h"
#include "Dijkstra.h"
#include "Dubins.h"
#include "Dubins_Curves.h"
#include <stdio.h>

using namespace std;
using namespace DubinsCurves;

#define INPUT_CPP_FILE "data_to_cpp.txt"
#define DATA_TO_MATLAB "data_to_matlab.txt"


int main()
{
	pyTxt2Cpp(INPUT_CPP_FILE);
	string InputFile(DATA_TO_MATLAB);
	ASTAR(InputFile);
	DIJKSTRA(InputFile);
	DIJKSTRA_DUBINS(InputFile);
	ASTAR_DUBINS(InputFile);

	return 0;
}

