
#include <iostream>
#include <fstream>
#include "GraphHandler.h"

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> Graph;

int main() {
    GraphHandler handler;
    Graph g = handler.readGraph("../data/football.graphml");
    handler.printGraph(g);
    return 0;
}
