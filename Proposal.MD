## CS 225 Data Structures 
## Project Proposal (cywang3-spate562-jmatz-pburle2)

### Leading Question
Using our dataset, we will implement a method that will recommend a user to different Twitch streamers based on their preferences (streamer partnership and profanity level) and current following. This would allow users to discover more streamers they would enjoy watching. We would also have a method that provides users with information on how two streamers are connected through a series of mutually following streamers on the shortest path.

### Dataset Acquisition and Processing: 
The dataset we’ve chosen is Twitch Games Social Network from Stanford data sets. The nodes represent Twitch users and the edges represent mutual follower relationships between the Twitch users. 
http://snap.stanford.edu/data/twitch-social-networks.html

We plan on downloading the data in the provided CSV format. Then we will pre-process the data using python to acquire additional information via the TwitchAPI. This additional information includes the Twitch display name of the user as well as the viewership count for the specified user. The downloaded dataset provided the user_id associated with each streamer, and the API call of GetUserByID will be used to perform this operation.
Once our data is pre-processed, we will transfer over to our C++ files and store the information within our custom TwitchUser objects. This will allow us to then develop and run the methods that are detailed in the section below.

### Graphing Algorithms: 
Because we intend to implement finding the shortest path, we would utilize a Breadth First Search algorithm. The estimated time complexity for BFS is O(V + E) where V represents the number of vertices and E represents the number of edges.
1. Shortest Path algorithm
* Dijkstra’s algorithm (Est. time complexity - O(V^2))
* Be able to figure out the shortest link between two specified twitch users
2. Visual Representation of the Data
* Draw a graph with node size dependent on user views
* Allows users to visualize the network and data
* We are unable to accurately predict time complexity for the creation of visual representation

Three deliverables
1. Visualization of the dataset(graph)
2. Command-line “command” that output the five most recommended users and their respective followers given an input of a username
3. Command-line “command” that outputs the shortest path given an input of two usernames.

### Timeline: 
1. By: 11/12 at the beginning of our weekly meeting(~2:00pm)
* Parse the data and get a modified dataset including twitch user-names and views
* Get comfortable with Twitch API and its capabilities
2. By: 11/19 at the beginning of our weekly meeting(~2:00pm)
* BFS traversal
* Testing for BFS
3. By: 11/26 at the beginning of our weekly meeting(~2:00pm)
* Shortest path algorithm completed
* Testing for shortest path
4. By: 12/3 at the beginning of our weekly meeting(~2:00pm)
* Progress on visualization(½)
* Testing for this part of visualization
5. By: 12/10 at the beginning of our weekly meeting(~2:00pm)
* Completed visualization w/ finishing touches
* Testing for remainder of visualization
6. By: 12/13
* Work on design
* Finish up testing
* Final video presentation

