#  Twitch Streamer Network Visualization and Analysis

## About the Project
This collaborative project seeks to visualize the connections between various Twitch streamers, and investigate whether or not we are able to discern "networks" of multiple streamers. Three main algorithms we implemented are Breadth-First Search, Dijkstra's Shortest Path, and an adaptation of the Fruchterman-Reingold force-directed graph. 

The code we developed for the project is contained within the base directory. We imported the Catch testing library and existing CS225 code from previous MPs and labs; the code is contained in the respective catch and cs225 folders. Objects and dependencies are stored inside the .objs folder and are not committed to the repository.

The python script we used to clean the data and alter the data to a desired format is in the **main.py** file in the base directory.

Images used in our report are contained in the images folder.

In order to use another set of data, two files are needed:
1. csv of streamer data formatted as:
	- index,TwitchID,age_in_days,has_mature_content,views,is_twitch_partner,convertedId,Twitch_username
2. csv of edge data formatted as:
	- convertedId,convertedId

In each of the main.cpp, shortest_path.cpp, and bfs.cpp files replace the existing paths to the included streamer data and edge data files with paths to the new streamer data and edge data files.

### Video Presentation Link: https://youtu.be/_AHaBpHF1QM
\
&nbsp;


## CSV Parsing, Streamer (Node) and Friend (Edge) Data

---

The Twitch Streamer datasets are located in the data folder. 
The modified English target data set contains the streamer data in the following format:
> index, TwitchID, age in days, mature content, views, twitch partner, convertedId, Twitch username

All code pertaining to the parsing of the data set is located in the CSVParser class. The parser class parses the node CSV and edge CSV files and constructs Streamer objects, storing all created Streamers into a vector that is then returned.

\
&nbsp;


## Graph Visualization

---

Logic for drawing all nodes and edges are in the graph_visual class, based on the **Fruchterman-Reingold** algorithm in structuring the shape of our dataset for repulsive and attractive forces. Graph images will be output to **original_graph.png** and **final_graph.png** in the base directory
#### To compile and create output graph images:
	make && ./visualize <image_dimensions> <num_streamers> <num_iterations>
>For the included dataset, we found that the arguments **8000**, **1000**, and **85** for **<image_dimensions>**, **<num_streamers>**, and **<num_iterations>** respectively create a visually-appealing graph that is representative of the entire dataset due to the nature of the Streamer data CSV already being in random order.

\
&nbsp;


## BFS and Dijkstra's Shortest Path, Utils

---

The graph class contains code for the **BFS** and **Dijkstra's** shortest path algorithms. The logic for calculating distances between two nodes as well as printing the path for two nodes is in the utils class. The BFS traversal is print in order to the console along with the number of nodes in that connected component. The shortest path from one streamer to another is printed to the console in the order from beginning to end.
#### To compile and run BFS:
    make bfs && ./bfs <start_id>
#### To compile and run Dijkstra:
	make shortest_path && ./shortest_path <start_name> <end_name>
>NOTE: Streamer names are case sensitive

\
&nbsp;

## Testing the Code

---

All tests pertaining to the classes are in the test folder. We have created separate test files for the four major source files involved in the project. Generally, our tests involve testing the major methods contained in our code, and private helper methods are tested by using publicly available methods. We compare results produced from our code to hard-coded, expected results that we have calculated ourselves. For trivial methods such as getters and setters, we generally refrained from create test cases. Utils also only contains a trivial distance calculation method and method that prints to console, so we decided not to implement utils tests to our testing suite. We also used subsets of our data for some test cases, and the subset CSVs are located in the data folder.
 
####  To compile tests:
	make test
#### To run all tests:
	./test
#### To run tests for specific classes:
	./test [class_name]
>Keep the square brackets and replace class_name with one of the following: graph, graph_visual, streamer, CSVParser
