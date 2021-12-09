#pragma once
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "streamer.h"

using namespace std;

/** Class that parses csvs (edges and node data) into Streamer objects. */
class CSVParser {
 public:
  /** Default constructor */
  CSVParser();

  /**
   * Parse csvs into edge and node data.
   *
   * @param filename Name of the file that contains node data.
   * @param filename_edges Name of the file that contains edge data.
   * @return vector containing Streamer objects parsed from the data
   */
  vector<Streamer> parseFile(string filename, string filename_edges);

  /**
   * Create a Streamer object from a string of data.
   *
   * @param line String containing Streamer data.
   * @return a Streamer object.
   */
  Streamer createStreamer(const string& line);

  /**
   * Parses edge data csv into map of Streamer and their friends (as ids).
   *
   * @param filename Name of the file that contains edge data
   */
  void parseFriends(string filename);

  map<unsigned, vector<unsigned>> getFriendsMap();

 private:
  map<unsigned, vector<unsigned>> friend_to_friend_;

  /**
   * Finds all friends of a Streamer given their id.
   *
   * @param id Id of Streamer to find friends of.
   * @return a vector of a Streamer's friends in id form.
   */
  vector<unsigned> findFriendsHelper(unsigned id);
};