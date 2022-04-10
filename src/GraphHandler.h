#ifndef INC_22S_PA03_GIRVAN_NEWMAN_KASPEREROY2_GRAPHHANDLER_H
#define INC_22S_PA03_GIRVAN_NEWMAN_KASPEREROY2_GRAPHHANDLER_H

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphml.hpp>
#include <boost/property_map/dynamic_property_map.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/copy.hpp>
#include <boost/graph/graphviz.hpp>

#include <iostream>
#include <fstream>
#include <map>

//testing
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/breadth_first_search.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> Graph;
using V = boost::graph_traits<Graph>::vertex_descriptor;

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

    // This function takes in a graph, and gets the distance from all Vertiecies to all other verticies
    // allPaths[0] would be the shortest path from vertex 0 to all other verticies
    // These paths are store as predecessors, meaning if allPaths[0][1] == 1, then the path from 0 to 1 is 0->1
    // If allPaths[0][2] == 1 and allPaths[0][1] == 0, then the path from 0 to 2 is 0->1->2
    std::vector<std::vector<V>> getPaths(Graph &g){
        std::vector<std::vector<V>> allPaths;
        auto VID = get(boost::vertex_index, g);
        boost::graph_traits <Graph>::vertex_iterator start, end;
        boost::tie(start, end) = boost::vertices(g);
        while(*start != *end) {
            //Source:https://cppsecrets.com/users/1453107109971219711010750555564103109971051084699111109/c00-boostGraphbreadthfirstsearch.php
            V curr_vertex = VID[*start];
            std::vector<V> currPredecesor(boost::num_vertices(g));
            boost::breadth_first_search(g, curr_vertex, boost::visitor(
                    boost::make_bfs_visitor(boost::record_predecessors(&currPredecesor[0], boost::on_tree_edge()))));
            allPaths.push_back(currPredecesor);
            start++;
        }
        //std::cout << allPaths.size() << std::endl;
        return allPaths;
    }
};


#endif //INC_22S_PA03_GIRVAN_NEWMAN_KASPEREROY2_GRAPHHANDLER_H
