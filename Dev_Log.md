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