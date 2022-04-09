//
// Created by Jeremy on 4/8/2022.
//

#ifndef INC_22S_PA03_GIRVAN_NEWMAN_KASPEREROY2_GRAPHHANDLER_H
#define INC_22S_PA03_GIRVAN_NEWMAN_KASPEREROY2_GRAPHHANDLER_H

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphml.hpp>
#include <boost/property_map/dynamic_property_map.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/copy.hpp>

#include <iostream>
#include <fstream>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> Graph;
class GraphHandler {
public:
    GraphHandler(){}
    Graph readGraph(std::string fileName){
            Graph g;
            boost::dynamic_properties dp(boost::ignore_other_properties);
            std::ifstream ifs(fileName);
            if(!ifs.is_open()) {
                std::cout << "Error opening file" << std::endl;
                return 1;
            }
            boost::read_graphml(ifs, g, dp);
            return g;
    }
    void printGraph(Graph &g){
        std::cout << "V = " << num_vertices(g) << " / E = " << num_edges(g) << std::endl;
        boost::print_graph(g);
    }
};


#endif //INC_22S_PA03_GIRVAN_NEWMAN_KASPEREROY2_GRAPHHANDLER_H
