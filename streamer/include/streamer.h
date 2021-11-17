#pragma once
#include <string>
#include <vector>

/* Object representing a Twitch streamer node with its connecting edges. */
class Streamer {
 public:
  Streamer();
  Streamer(unsigned id, std::string name, unsigned views, unsigned age,
           vector<unsigned> friends);

  unsigned getId() const;
  std::string getName() const;
  unsigned getViews() const;
  unsigned getAge() const;
  bool isFriend(unsigned id) const;

 private:
  unsigned id_;
  std::string name_;
  unsigned views_;
  unsigned age_;
  std::vector<unsigned> friends_;
};