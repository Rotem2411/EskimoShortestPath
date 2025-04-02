# EskimoShortestPath

This project implements and compares **Dijkstra** and **A-Star (A\*)** shortest path algorithms, with and without **Dubins path** constraints, in a 2D environment with polygonal obstacles. It is designed for use in robotics, autonomous navigation, or any domain where realistic path planning (e.g., turning radius constraints) is essential.

## 🚀 Features

- ✅ Classic Dijkstra's algorithm
- ✅ A\* algorithm with heuristics
- ✅ Dubins path planning (minimum turning radius)
- ✅ Polygonal obstacle avoidance
- ✅ Visualization tools for path planning

## 🗂️ Project Structure

```
EskimoShortestPath/
│
├── A-STAR/              # A* implementation
├── Dubins_Curves/       # Dubins path generator and utilities
├── convexhull/          # Utilities for convex hull generation
├── polygons/            # Environment and obstacle generation
├── test/                # Test scenarios
└── ...
```

## 🧰 Technologies Used

- C++
- Standard Template Library (STL)
- OpenCV (optional, for visualization)
- Custom geometric utilities

## 🧪 How to Run

1. Clone the repository:
   ```bash
   git clone https://github.com/Rotem2411/EskimoShortestPath.git
   cd EskimoShortestPath
   ```

2. Compile using `g++` or your preferred C++ compiler:
   ```bash
   g++ -std=c++11 -o main main.cpp
   ./main
   ```

   > Replace `main.cpp` with the appropriate file depending on the algorithm you want to test.

3. (Optional) If using OpenCV for visualization, make sure it's installed and linked during compilation.

## 📌 TODO

- [ ] Integrate GUI for inputting start/end points
- [ ] Benchmark performance across algorithms
- [ ] Add support for 3D path planning

## 📜 License

This project is licensed under the MIT License — see the [LICENSE](LICENSE) file for details.

---

Feel free to fork, contribute, or raise issues if you find bugs or want to request features!
