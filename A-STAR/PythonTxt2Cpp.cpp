#include "PythonTxt2Cpp.h"

bool pyTxt2Cpp(string input_file)
{
    Generator world;
    world.pyTxt2Cpp(input_file);
    return 1;
}
