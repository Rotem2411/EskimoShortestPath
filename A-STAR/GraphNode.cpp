#include "GraphNode.h"


float Node::distance2Nodes(Node start, Node dest)
{
    return float((sqrt(pow(dest.p.getX() - start.p.getX(), 2) + pow(dest.p.getY() - start.p.getY(), 2))));
}

float distance2points(Point2D start, Point2D dest)
{
    return float((sqrt(pow(dest.getX() - start.getX(), 2) + pow(dest.getY() - start.getY(), 2))));
}

void Obstacle::createObstacle(Polygon poly)
{
    m_NumNodes = poly.getNumPoints();
    int count;
    for (count = 0; count < m_NumNodes; count++) {
        m_nodes[count] = Node(poly.getPoint()[count].getX(), poly.getPoint()[count].getY());
        m_nodes[count].m_nodeIdx = count;
        if (count > 0) // create edge in the polygon if not the first node
            ObstacleEdges[count - 1] = GraphEdge(m_nodes[count - 1], m_nodes[count]);
    }
    // create edge from last node to the first node
    ObstacleEdges[count - 1] = GraphEdge(m_nodes[count - 1], m_nodes[0]);
}

bool Obstacle::checkObstacleIntersection(Node start, Node end, GraphEdge* ObstacleEdges, int numObstacleEdges) {
    for (int i = 0; i < numObstacleEdges; i++) {
        if (Graph::Lineintersection(start.p, end.p, ObstacleEdges[i].start.p, ObstacleEdges[i].end.p))
            return true;
    }
    return false;
}

bool Obstacle::isPointInsidePoly(Node test)
{
    bool result = false;
    for (int i = 0, j = m_NumNodes - 1; i < m_NumNodes; j = i++)
    {
        if ((m_nodes[i].p.getY() > test.p.getY()) != (m_nodes[j].p.getY() > test.p.getY()) &&
            (test.p.getX() < (m_nodes[j].p.getX() - m_nodes[i].p.getX()) * (test.p.getY() - m_nodes[i].p.getY()) / (m_nodes[j].p.getY() - m_nodes[i].p.getY()) + m_nodes[i].p.getX()))
            result = !result;     
    }
    return result;
}

void Graph::createGraph(Node* node, int numNodes, Obstacle* o, int numObstacles)
{
    m_numNodes = numNodes;
    for (int i = 0; i <= numNodes; i++)
        m_Nodes[i] = node[i];
    for (int i = 0; i <= numNodes; i++)
        for (int k = 0; k < numObstacles; k++)
            if (o[k].isPointInsidePoly(m_Nodes[i]) && m_Nodes[i].m_polygonIdx!=k) //not intersect a polygon
                m_Nodes[i].inside_polygon = true;
    createMatrix(o, numObstacles);
}

bool Graph::Lineintersection(Point2D A, Point2D B, Point2D C, Point2D D) {
    // Line AB represented as a1x + b1y = c1
    double a1 = B.getY() - A.getY();
    double b1 = A.getX() - B.getX();
    double c1 = a1 * (A.getX()) + b1 * (A.getY());
    // Line CD represented as a2x + b2y = c2
    double a2 = D.getY() - C.getY();
    double b2 = C.getX() - D.getX();
    double c2 = a2 * (C.getX()) + b2 * (C.getY());
    double det = a1 * b2 - a2 * b1;
    if (abs(det) <= EPSILON) {
        return false;
    }
    else {
        double x = (b2 * c1 - b1 * c2) / det;
        double y = (a1 * c2 - a2 * c1) / det;
        if (x == -0.0) x = 0;
        if (y == -0.0) y = 0;
        if ((x > min(A.getX(), B.getX()) && x < max(A.getX(), B.getX())) && (y > min(A.getY(), B.getY()) && y < max(A.getY(), B.getY())) &&
            (x > min(C.getX(), D.getX()) && x < max(C.getX(), D.getX())) && (y > min(C.getY(), D.getY()) && y < max(C.getY(), D.getY())))
            return true;
        return false;
    }
}

void Graph::writeMatrixToTxt(string output_file)
{
    ofstream outputFile(output_file);
    if (outputFile.is_open())
    {       
        for (int i = 0; i <= m_numNodes; i++) {
            for (int j = 0; j <= m_numNodes; j++)
            {
                outputFile << matrix[i][j] << " ";
            }
            outputFile << "\n";
        }
        outputFile.close(); // close output file
    }
    else
        cout << "can't create the new file \n";
}

bool Graph::checkObstaclesIntersection(Node start, Node end, Obstacle* Obstacles, int numObstacles)
{
    for (int i = 0; i < numObstacles; i++) {
        if (start.m_polygonIdx == end.m_polygonIdx)
            if (abs(start.m_nodeIdx - end.m_nodeIdx) != 1) 
                if (abs(start.m_nodeIdx - end.m_nodeIdx) != (Obstacles[start.m_polygonIdx].m_NumNodes - 1))
                    return true;
        if (Obstacle::checkObstacleIntersection(start, end, Obstacles[i].ObstacleEdges, Obstacles[i].m_NumNodes))
            return true;
    }
    return false;
}

void Graph::createMatrix(Obstacle* o, int numObstacles)
{
    for (int k = 0; k < numObstacles; k++)
        for (int i = 0; i < m_numNodes; i++) 
        {
            if (m_Nodes[i].inside_polygon == true) 
                continue;
            for (int j = 0; j <= m_numNodes; j++)
            {
                if (i == j)
                    continue;
                if (m_Nodes[j].inside_polygon == true) 
                    continue;
                if (matrix[i][j] == NULL) // not visit yet
                {
                    if (!checkObstaclesIntersection(m_Nodes[i], m_Nodes[j], o, numObstacles)) 
                    {
                        matrix[i][j] = Node::distance2Nodes(m_Nodes[i], m_Nodes[j]);
                        matrix[j][i] = matrix[i][j];
                    }
                }
            }
        }
}

void Path::printPath(Node start, Node goal)
{
    if (goal == start) {
        cout << '(' << start.p.getX() << ", " << start.p.getY() << ") ";
        return;
    }
    cout << '(' << goal.p.getX() << ", " << goal.p.getY() << ") -> ";
    printPath(start, *goal.parant);
}

int Path::miniDist(float distance[], bool Tset[], int NumNodes) // finding minimum distance
{
    float minimum = FLT_MAX;
    int id_x = 0;
    for (int k = 0; k <= NumNodes; k++)
    {
        if (Tset[k] == false && distance[k] <= minimum)
        {
            minimum = distance[k];
            id_x = k;
        }
    }
    return id_x;
}

void Path::DijkstraAlgo(Node start, Node goal, Graph graph)
{
    float distance[MAX_NODES]; // // array to calculate the minimum distance for each node                             
    bool Tset[MAX_NODES];// boolean array to mark visited and unvisited for each node
    for (int k = 0; k <=graph.m_numNodes; k++)
    {
        distance[k] =FLT_MAX;
        Tset[k] = false;
    }
    distance[0] = 0;   // Source vertex distance is set 0               
    for (int k = 0; k <= graph.m_numNodes; k++)
    {
        int m = miniDist(distance, Tset, graph.m_numNodes);
        Tset[m] = true;
        for (int k = 0; k <= graph.m_numNodes; k++)
        {
            // updating the distance of neighbouring vertex
            if (!Tset[k] && graph.matrix[m][k] && distance[m] != FLT_MAX && distance[m] + graph.matrix[m][k] < distance[k]) {
                distance[k] = distance[m] + graph.matrix[m][k];
                graph.m_Nodes[k].parant = &graph.m_Nodes[m];
            }
        }
    }
    for (int k = 0; k <= graph.m_numNodes; k++) {
        if (start == graph.m_Nodes[k])
            start = graph.m_Nodes[k];
        if (goal == graph.m_Nodes[k])
            goal = graph.m_Nodes[k];
    }
    cout << "Vertex\t\t\t\t\tDistance from source vertex" << endl;
    for (int k = 0; k <= graph.m_numNodes; k++)
    {
        cout <<'('<< graph.m_Nodes[k].p.getX() << ", " << graph.m_Nodes[k].p.getY() << ')' << "\t\t\t" << distance[k] << endl;
    }
    Node temp = goal;
    while (temp != start) {
        m_PathNodes[m_PathNumNodes] = temp;
        temp = *temp.parant;
        m_PathNumNodes++;
    }
    m_PathNodes[m_PathNumNodes] = start;
    m_PathNumNodes++;
}

void Path::writePathToTxt(Node start, Node goal, string output_file)
{
    ofstream outputFile(output_file);
    if (outputFile.is_open())
    {
        while (goal != start) {
            outputFile << goal.p.getX() << " " << goal.p.getY() << "\n";
            goal = *goal.parant;
        }
        outputFile << start.p.getX() << " " << start.p.getY() << "\n";
        outputFile.close(); // close output file
    }
    else
        cout << "can't create the new file \n";
}

bool Generator::read_txt_file(string input_file)
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

void Generator::create_txt_file(Map map, Point2D src, Point2D dst, int NumPolygons, string output_file)
{
    ofstream outputFile(output_file); //initial output file
    outputFile << map.width() << "\n" << map.height() << "\n";
    outputFile << src.getX() << " " << src.getY() << "\n";
    outputFile << dst.getX() << " " << dst.getY() << "\n";
    outputFile << NumPolygons << "\n";
    return;
}

void Generator::write_txt_file(Polygon p, string output_file)
{
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

void Generator::generateWorld()
{
    numNodes = 0;
    o = new Obstacle[MAX_POLYGONS]; // initial obstacle array
    Map map((int)numbersArr[0], (int)numbersArr[1]); //initial map
    Point2D p_src(numbersArr[2], numbersArr[3]);// source of the eskimo
    dst = Node(numbersArr[4], numbersArr[5]); // destination of the eskimo
    src = Node(p_src, dst, INT_MIN);
    Nodes[numNodes++] = src;
    numPolygons = (int)numbersArr[6]; // number of polygons
    for (int j = 0, i=7; j < numPolygons; j++) {
        float x, y;
        int dots = (int)numbersArr[i++]; // number of points in the polygon
        Point2D* points = (Point2D*)malloc(dots * sizeof(Point2D));
        for (int numOfPointsInPolygon = 0; numOfPointsInPolygon < dots; numOfPointsInPolygon++)
        {
            x = numbersArr[i++];
            y = numbersArr[i++];
            points[numOfPointsInPolygon] = Point2D(x, y);
            Nodes[numNodes] = Node(points[numOfPointsInPolygon], dst, j);
            Nodes[numNodes].m_nodeIdx = numOfPointsInPolygon;
            if (numOfPointsInPolygon > 0) {
                Nodes[numNodes].prev = &Nodes[numNodes - 1];
                Nodes[numNodes - 1].next = &Nodes[numNodes];
            }
            numNodes++;
        }
        Nodes[numNodes - dots].prev = &Nodes[numNodes - 1];
        Nodes[numNodes - 1].next = &Nodes[numNodes - dots];
        if (stPolygons.addPolygon(points, dots))
            o[j].createObstacle(stPolygons.getPolygons()[j]);
        free(points);
    }
    Nodes[numNodes] = dst;
}

bool Generator::pyTxt2Cpp(string input_file)
{
    if (!read_txt_file(input_file))
        return 1; //read txt file
    Map map((int)numbersArr[0], (int)numbersArr[1]); //initial map
    Point2D src(numbersArr[2], numbersArr[3]); // source of the eskimo
    Point2D dst(numbersArr[4], numbersArr[5]); // destination of the eskimo
    int NumPolygons = (int)numbersArr[6]; // number of polygons
    create_txt_file(map, src, dst, NumPolygons, DATA_TO_MATLAB);
    Polygons stPolygons;
    for (int j = 0,i=8; j < NumPolygons; j++,i++) {
        int dots = (int)numbersArr[i++]; // number of points in the polygon
        Point2D* points = (Point2D*)malloc(dots * sizeof(Point2D));
        float x, y;
        for (int count = 0; count < dots; count++) {
            x = numbersArr[i++];
            y = numbersArr[i++];
            points[count] = Point2D(x, y);
        }
        if (stPolygons.addPolygon(points, dots))
            stPolygons.getPolygons()[j].setPolygon(points, dots);
        stPolygons.getPolygons()[j].convex_hull();
        free(points);
    }
    for (int count = 0; count < stPolygons.getNumOfPolygons(); count++) {
        write_txt_file(stPolygons.getPolygons()[count], DATA_TO_MATLAB);
    }
    return 0;
}