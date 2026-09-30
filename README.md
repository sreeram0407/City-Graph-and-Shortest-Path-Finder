# City Graph & Shortest Path Finder

A C++ implementation of Dijkstra’s algorithm for weighted city graphs. It uses adjacency lists and a minimum priority queue to find shortest paths from a selected source city.

## Build and run

From the repository root:

```bash
g++ -std=c++11 main.cpp -o city_paths
./city_paths
```

## Input format

1. Enter the number of cities.
2. Enter one adjacency-list line per city: `City,Neighbor(distance),...`.
3. Enter the source city.
4. Enter `yes` to query another source, or `no` to finish.

Use a trailing comma on every adjacency-list line. Example:

```text
3
A,B(5),C(12),
B,A(5),C(3),
C,A(12),B(3),
A
no
```

The program prints the graph and shortest-path results. Use nonnegative edge weights for Dijkstra’s algorithm.

## Files

- [main.cpp](main.cpp): graph input and interactive source selection.
- [Graph.h](Graph.h): graph representation and Dijkstra’s algorithm.
- [ArrivalCityList.h](ArrivalCityList.h): adjacency lists.
- [MinPriorityQueue.h](MinPriorityQueue.h): priority queue.

**Author:** Sreeram Kondapalli
