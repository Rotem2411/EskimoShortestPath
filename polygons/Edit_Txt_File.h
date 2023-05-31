#pragma once
#include <iostream>
#include <fstream>
#include "Polygons.h"
#include "Map.h"

using namespace std;

#define INPUT_NUMBERS 650 

class edit_txt_file {
public:
	static float numbersArr[INPUT_NUMBERS]; // array to store numbers from the file

	static bool read_txt_file(string input_file);
	static void create_txt_file(Map map, Point2D src, Point2D dst, int NumPolygons, string output_file);
	static void write_txt_file(Polygon p, string output_file);
};


