# cywang3-pburle2-spate562-jamatz2
CS 225 Final Project Fall 2021 

The twitch streamer datasets are located in the data folder. The modifed english target data set contains the index, TwitchID, age in days, mature content, views, twitch partner, convertedId, and Twitch username. All tests pertaining to the classes are in the test folder. All code pertaining to the parsing of the data set is located in the CSVParser class. The Graph class contains code for the BFS and Dijkstra's shortest path algorithms. The logic for calculating distances between two nodes as well as printing the path for two nodes is in the util class. Logic for drawing all nodes and edges are in the graph visual class, based on the fruchterman reingold algorithm in structuring the shape of our dataset for repulsive and attractive forces. The output of our visualization png is in the main folder.

To run the bfs:
make bfs && ./bfs <start_id>

To run Dijkstra:
make shortest_path && ./shortest_path <start_name> <end_name> [NOTE: Names are case sensitive]

To output graph:
make && ./visualize <image_dimensions> <num_streamers> <num_iterations>

To run tests:
make test
  * To run all tests:
      ./test test
  * To run only graph tests:
      ./test [Graph]
  * To run only visual test:
      ./test [visual]
