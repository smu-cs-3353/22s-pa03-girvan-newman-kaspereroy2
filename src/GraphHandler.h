#ifndef INC_22S_PA03_GIRVAN_NEWMAN_KASPEREROY2_GRAPHHANDLER_H
#define INC_22S_PA03_GIRVAN_NEWMAN_KASPEREROY2_GRAPHHANDLER_H

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphml.hpp>
#include <boost/property_map/dynamic_property_map.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/copy.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/connected_components.hpp>
#include <iostream>
#include <fstream>
#include <map>
#include <stack>
#include <utility>
#include <algorithm>
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

    std::pair<int,int> getHighestBetweenness(Graph &g, std::vector<std::vector<V>> &allPaths){
        //Key = edge pair, value = number of times it is crossed
        std::map<std::pair<int,int>,int> betweennessValues;

        //Loop through all starting vertices
        for(int start=0; start<allPaths.size(); start++){
            //Loop through all end vertices
            for(int end=0; end<allPaths.at(start).size(); end++){
                //used to store the path to get from end to start
                std::stack<int> currPath;
                int currPos = end;


                //check to make sure that there is a valid path because the allPaths will show a '0' if the
                //dfs could not reach a vertex
                bool noPath = false;
                int prevPos = -1;
                //Adds the specific path to the stack
                while(currPos != start){
                    //if the edge does not exist
                    if(prevPos != -1 && edge(prevPos,currPos,g).second == 0){
                        noPath = true;
                        break;
                    }
                    currPath.push(currPos);
                    prevPos = currPos;
                    currPos = allPaths.at(start).at(currPos);
                }

                //This means that there is no path from start to end, continue not break!
                if(noPath){
                    continue;
                }
                //pair1 and pair2 hold the edge values (the key in the map)
                int pair1 = start;
                int pair2;

                //Loops through the path, grabbing the edge pairs one at a time
                while(!currPath.empty()){
                    pair2 = currPath.top();

                    //Yet another check to make sure the path exists because edge cases and stuff
                    if(edge(pair1,pair2,g).second == 0){
                        break;
                    }
                    std::pair<int,int> temp;
                    //Make sure that first is always the smallest so (1,0) becomes (0,1) so they can be summed correctly
                    temp.first = std::min(pair1,pair2);
                    temp.second = std::max(pair1,pair2);
                    auto it = betweennessValues.find(temp);
                    if(it == betweennessValues.end()){//not yet in map
                        betweennessValues.insert({temp,1});
                    }
                    else{
                        it->second ++;
                    }
                    pair1 = pair2;
                    currPath.pop();
                }

            }//end inner for (end vertices)
        }//end outer for (starting vertices)

        //Loop through the map to find the edge that was traversed the most
        auto maxTraversed= betweennessValues.begin();
        for(auto it=betweennessValues.begin(); it!=betweennessValues.end(); it++){
            if(it->second > maxTraversed->second){
                maxTraversed = it;
            }
            //For Testing stuff and stuff
            //std::cout << "Edge: ("<< it->first.first << ", " << it->first.second << ") Times Traversed:" << it->second << std::endl;
        }
        //std::cout << "Max Edge: (" << maxTraversed->first.first << ", " << maxTraversed->first.second << ") Times Traversed: " << maxTraversed->second << std::endl;
        return maxTraversed->first;
    }//end getHighestBetweenness


    //Takes in Graph g and a stopping point for the algorithm
    //The function repeatedly calculates the paths of the current graph, and calculates which path is traversed
    //The most before removing it and looping until the desired # of groups are reached.
    void girvanNewman(Graph& g, int desired_groups){
       // printGraph(g);
        while(num_edges(g)!= 0){
            std::vector<int> useThis (boost::num_vertices (g));
            auto num_groups =  boost::connected_components (g, &useThis[0]);
            //std::cout << num_groups << std::endl;
            if(num_groups >= desired_groups){
                break;
            }
            auto paths = getPaths(g);
            /* for error handling
            std::cout<<"PATHS:"<<std::endl;
            for(int j=0; j<paths.size();j++){
                std::cout << j << ")";
                for(int k=0; k<paths.at(j).size(); k++){
                    std::cout<< paths.at(j).at(k) << " ";
                }
                std::cout<<std::endl;
            }
            std::cout << paths.size() << std::endl;
             */
            auto highestBetweenness = getHighestBetweenness(g,paths);
            remove_edge(highestBetweenness.first,highestBetweenness.second,g);
            //std::cout << "Removed (" << highestBetweenness.first << "," << highestBetweenness.second << ")" << std::endl;
            //printGraph(g);
        }
        //Final Graph
        printGraph(g);
    }
    //p
    void writeGraphViz(Graph& g, std::string fileName){
        std::ofstream outputFile(fileName);
        boost::write_graphviz(outputFile,g);
    }
    void writeGraphml(Graph& g, std::string fileName){
        std::ofstream outputFile(fileName);
        boost::dynamic_properties dp(boost::ignore_other_properties);
        boost::write_graphml(outputFile,g,dp,true);
    }
};

#endif //INC_22S_PA03_GIRVAN_NEWMAN_KASPEREROY2_GRAPHHANDLER_H
