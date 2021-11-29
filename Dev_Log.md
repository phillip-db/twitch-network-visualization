## Project Dev Log

### Week of Nov 12 (pburle2)
* Updated our proposal according to Soham's feedback
    * Define edge weights based on account ages difference
    * Adjust leading question to include both algorithms
    * Choose specificall to use force-directed graph visualizatition
    
* Setup Twitch development environment for Twitch API access

#### TODO this weekend:

(delayed b/c of proposal rework)

* Create python script that accesses API and maps usernames to new IDs in data set
    * Input list of Twitch numerical IDs
    * Ouput list of Twitch usernames
    * Map Twitch username to dataset ID, append it to CSV using Pandas

* Create Streamer object class in C++
    * ID
    * Username
    * Views
    * Age
    * Follow

* Create wrapper class in C++
    * Read CSVs and create Streamer objects


### Week of Nov 20 (jamatz2)
* Completed parsing of initial dataset into readable format(CSV)
* Partially through completion of make file
* Completed streamer (node) class
    
#### TODO this weekend:

* Finish BFS

* Finish make file

* Testing for BFS

* Create CSV parser class
    * One method parses the data for the streamer
    * One method parses the connections between nodes

### Week of Nov 29 (spate562)
* Created a CSV Parser class to read CSV into our Streamer Objects
* Implemented basic graph methods in-order to construct our graph
* Finish make file

Note: We are currently behind schedule due to Thanksgiving break
    
#### TODO this week:

* Finish graph class implementation

* Start BFS

* Additional testing