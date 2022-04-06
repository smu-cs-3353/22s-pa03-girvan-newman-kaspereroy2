//
// Created by Jeremy on 4/6/2022.
//

#include "Graph.h"

Graph::Graph() {
    numVert = 0;
    numEdges = 0;
}

Graph::Graph(int numVertices) {
    numVert = numVertices;
    numEdges = 0;
    for(int i=0; i<numVert ; i++) {
        LinkedList<int> temp;
        adjList.push_back(temp);
    }
}

Graph::~Graph() {}

void Graph::print() {
    // TODO
    //LinkedList
    for(int i=0; i<numVert; i++){
        std::cout << i << "";

    }
}

void Graph::addEdge(int v1, int v2) {
    adjList.at(v1).push_back(v2);
    adjList.at(v2).push_back(v1);
    numEdges++;
}

