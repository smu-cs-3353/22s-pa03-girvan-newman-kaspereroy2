//
// Created by Jeremy on 4/6/2022.
//

#ifndef GIRVAN_NEWMAN_KASPEREROY_GRAPH_H
#define GIRVAN_NEWMAN_KASPEREROY_GRAPH_H

#include "LinkedList.h"
class Graph {
private:
    LinkedList<LinkedList<int>> adjList;
    int numEdges;
    int numVert;
public:
    Graph();
    Graph(int numVertices);
    ~Graph();
    void print();
    void addEdge(int v1, int v2);
};


#endif //GIRVAN_NEWMAN_KASPEREROY_GRAPH_H
