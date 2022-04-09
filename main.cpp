
#include <iostream>
#include <fstream>
//Boost Includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphml.hpp>
#include <boost/property_map/dynamic_property_map.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/copy.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> Graph;
//typedef boost::dynamic_properties Dproperty;

int main() {
    Graph g;
    boost::dynamic_properties dp(boost::ignore_other_properties);
    std::ifstream ifs("../data/football.graphml");
    if(!ifs.is_open()) {
        std::cout << "Error opening file" << std::endl;
        return 1;
    }
    boost::read_graphml(ifs, g, dp);

    return 0;
}
