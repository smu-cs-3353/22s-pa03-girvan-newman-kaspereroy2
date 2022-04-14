# PA03: Community Detection In Networks
London Kasper, Jeremy Waibel, Hazel Eroy
CS 3353 Spring 2022

### Summary
In this program, we were tasked with finding communities from a given graph dataset. 
Based on that, we created and handled a graph through the Boost Graph Library (BGL) and implemented a popular community detection algorithm, the Girvan-Newman algorithm, to find the communities.

### Usage
This program takes a graphml file and populates an adjacency list that we visually think of as a graph. 
Then, detects communities based on node connections. 
In this example, we are using data from data from a network of American football games between Division IA colleges during regular season Fall 2000. Example input file:


![](https://raw.githubusercontent.com/smu-cs-3353/22s-pa03-girvan-newman-kaspereroy2/main/images/data.png)

The input file above is a .gml, and can be converted to graphml file using the convertGML.py script. 
The input fill will be converted to the file below:

<br>![](https://raw.githubusercontent.com/smu-cs-3353/22s-pa03-girvan-newman-kaspereroy2/main/images/converted.png) <br>

We then use our implementation of the Girvan-Newman Algorithm on the newly created graphml file to detect communities in a new graphml file. Output file example:
<br> ![](https://raw.githubusercontent.com/smu-cs-3353/22s-pa03-girvan-newman-kaspereroy2/main/images/output.png)

The file above is sorted into its communities but the nodes no longer have their names. Based on the method we implemented to store our initial file into a graph that we can use our implementation of Girvan-Newman on, we had to discard the extra attributes associated with the nodes. In this case, we had to discard the names of the teams in each node.

To reintroduce names of the nodes, we used the original dataset and the graphRecon.ipynb file in our project to reassign names to their respective nodes.

Once reassigned, the graphRecon.ipynb file is used to generate community visualization.


<br>![](https://raw.githubusercontent.com/smu-cs-3353/22s-pa03-girvan-newman-kaspereroy2/main/src/graph.png)

The visualization above reflects the communities in the original Girvan-Newman community detection research paper.

In addition to implementing this algorithm for the football dataset used in the previous example, we also created random graphs with graphGen.ipynb and tested them against our implementation.


Check our medium series to learn about our extension!
https://medium.com/@jeremywaibel/girvan-newman-introuction-1a296c67d89e




