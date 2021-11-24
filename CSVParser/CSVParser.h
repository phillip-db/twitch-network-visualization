#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include "../streamer/streamer.h"


using namespace std;

class CSVParser {
    public:
        CSVParser();
        vector<Streamer> parseFile(string filename, string filename_edges);
        Streamer createStreamer(const string& line);
        void parseFriends(string filename);
        vector<unsigned> findFriendsHelper(unsigned id);

        map<unsigned, vector<unsigned>> getFriendsMap();

    private:
        map<unsigned, vector<unsigned>> friend_to_friend_;

};