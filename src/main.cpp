
#include <iostream>
#include <fstream>
#include "GraphHandler.h"

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> Graph;


int main() {
    GraphHandler handler;
    Graph g = handler.readGraph("../data/football.graphml");
    auto stuff = handler.getPaths(g);
    //handler.printGraph(g);
    //std::cout << "Idk: " << boost::vertices(g).first << std::endl;
    return 0;
}
