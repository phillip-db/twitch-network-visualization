# CS 225 Final Project Fall 2021 - cywang3-pburle2-spate562-jamatz2


## Data: 

The twitch streamer datasets are located in the data folder.

The modifed english target data set contains is comma-delimited in this order: 
>index, TwitchID, age in days, mature content, views, twitch partner, convertedId, Twitch Username 

## Tests:
All tests pertaining to the classes are in the test folder. 

- CSVParser tests are located in tests-CSVParser.cpp
- graph_visual tests are located in tests-graph_visual.cpp
- graph tests are located in tests-graph.cpp
- Streamer tests are located in tests-streamer.cpp

## Code:

The **CSVParser** class contains all code pertaining to the parsing of the initial data set from a CSV.

The **Graph** class contains code for the BFS and Dijkstra's shortest path algorithms. This class also constructs the adjacency matrix that we use to analyze our vertices and edges.

The **utils** class has the logic for calculating distances between two nodes as well as printing the path for two nodes.


The **graph_visual** class has the logic for the force-directed arrangement of our nodes. It also has the method for drawing all nodes and edges. The arrange method of this class uses several other methods and operator overloads located within in the fdpoint namespace within this class.

The **Streamer** class has the code for creating our custom Streamer object. This object stores all the attributes belonging to a streamer that we take from our dataset.

**Main.py** contains the code we used in conjuction with the Twitch API to preprocess our data as well as add additonal data such as the usernames of the Twitch Streamers.

## Modifying Data Input:

You can go into the main.cpp file and change the filepaths that are passed into the parser.parseFile() method in order to change the data. The first filepath is the CSV representing the information of each streamer. The second filepath is a CSV representing the edge connection between each node, represented by line with the first and second value in each line representing the id of two nodes that share an edge. The id's correspond to the convertedId that is present in the first file.

---

## To run BFS:

**Input:** A number representing the id of the streamer where you want to begin the BFS

```
make bfs && ./bfs <start_id>
```

**Output:** Outputs entire BFS traversal to terminal as a string

---

## To run Dijkstra's: 

**Input:** Two strings representing the streamers names, one for the *start streamer* and the other for *end streamer*

**NOTE:** Streamer names are case sensitive

```
make shortest_path && ./shortest_path <start_name> <end_name> 
```

**Output:** Outputs string of shortest path names to terminal

---

## To create visualization:

**Input:** 
1. The size of the image in pixels
2. The number of streamers to visualize initially
3. The number of times to run the positioning algorithm

>**Note**: When testing our code, we came to an optimal set of parameters that best demonstrated our code and is the most visually pleasing. These parameters will generate the initial and final images within our images folder as well as those included in Results.MD

>These parameters are: size = 8000, streamers = 1000, iterations = 85



```
make && ./visualize <image_dimensions> <num_streamers> <num_iterations>
```

**NOTE:** Takes up to a minute to run.

**Output:** Outputs images to main directory as **"original_graph.png"** and **"final_graph.png"**

---

## To run tests:
```
make test
```
  * To run all tests:
      ```
      ./test test
      ```
  * To run only graph tests:
      ```
      ./test [Graph]
      ```
  * To run only visual test:
      ```
      ./test [visual]
      ```
