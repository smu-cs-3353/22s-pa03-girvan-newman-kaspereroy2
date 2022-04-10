
#include <iostream>
#include <fstream>
#include "GraphHandler.h"

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> Graph;


int main() {
    GraphHandler handler;
    Graph g = handler.readGraph("../data/football.graphml");
    handler.girvanNewman(g,11);
    handler.writeGraphml(g,"../results/football11.graphml");

    return 0;
}
