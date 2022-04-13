#include <string>
#include "GraphHandler.h"

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> Graph;


int main(int argc, char* argv[]) {
    GraphHandler handler;
    std::string graphmlFile = argv[1];
    Graph g = handler.readGraph(graphmlFile);
    int desiredGroups = atoi(argv[2]);
    handler.girvanNewman(g,desiredGroups);
    std::string outputFile = argv[3];
    handler.writeGraphml(g,outputFile);

    return 0;
}

