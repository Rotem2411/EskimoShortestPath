#include "Edit_Txt_File.h"


bool read_txt_file(string input_file, float numbersArr[INPUT_NUMBERS]) {
    ifstream inputFile(input_file); // open input file
    if (!inputFile.is_open()) {
        cout << "Error opening file";
        return false;
    }
    string s;
    int i = 0;
    while (inputFile >> s) {
        if (atof(s.c_str()) != 0.0)
            numbersArr[i++] = float(atof(s.c_str()));
        else
            cout << "input not correct. string '" << s << "' should remove" << "\n";
    }
    inputFile.close(); // close input file
    return true;
}

void create_txt_file(Map map, Point2D src, Point2D dst, int NumPolygons, string output_file) {
    ofstream outputFile(output_file); //initial output file
    outputFile << map.width() << "\n" << map.height() << "\n";
    outputFile << src.getX() << " " << src.getY() << "\n";
    outputFile << dst.getX() << " " << dst.getY() << "\n";
    outputFile << NumPolygons << "\n";
    return;
}

void write_txt_file(Polygon p, string output_file) {
    ofstream outputFile(output_file, ios_base::app);
    if (outputFile.is_open())
    {
        outputFile << p.getNumPoints() << "\n";
        for (int k = 0; k < p.getNumPoints(); k++)
        {
            outputFile << p.getPoint()[k].getX() << " " << p.getPoint()[k].getY() << "\n";
        }
        outputFile.close(); // close output file
    }
    else
        cout << "can't create the new file \n";
}

bool edit_txt_file::read_txt_file(string input_file)
{
    ifstream inputFile(input_file); // open input file
    if (!inputFile.is_open()) {
        cout << "Error opening file";
        return false;
    }
    string s;
    int i = 0;
    while (inputFile >> s) {
        if (atof(s.c_str()) != 0.0)
            numbersArr[i++] = float(atof(s.c_str()));
        else
            cout << "input not correct. string '" << s << "' should remove" << "\n";
    }
    inputFile.close(); // close input file
    return true;
}

void edit_txt_file::create_txt_file(Map map, Point2D src, Point2D dst, int NumPolygons, string output_file)
{
    ofstream outputFile(output_file); //initial output file
    outputFile << map.width() << "\n" << map.height() << "\n";
    outputFile << src.getX() << " " << src.getY() << "\n";
    outputFile << dst.getX() << " " << dst.getY() << "\n";
    outputFile << NumPolygons << "\n";
    return;
}

void edit_txt_file::write_txt_file(Polygon p, string output_file)
{
    ifstream inputFile(output_file); // open input file
    if (!inputFile.is_open()) {
        cout << "Error opening file";
        return;
    }
    string s;
    int i = 0;
    while (inputFile >> s) {
        if (atof(s.c_str()) != 0.0)
            numbersArr[i++] = float(atof(s.c_str()));
        else
            cout << "input not correct. string '" << s << "' should remove" << "\n";
    }
    inputFile.close(); // close input file
    return;
}
