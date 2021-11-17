#include "streamer.h"
#include <algorithm>

Streamer() {}

Streamer(unsigned id, std::string name, unsigned views, unsigned age,
         std::vector<unsigned> friends)
    : id_(id), name_(name), views_(views), age_(age) {
  std::sort(friends);
  friends_ = friends;
}

bool isFriend(unsigned id) const {
  for (unsigned i = 0; i < friends_.size(); i++) {
    if (friends_[i] == id) {
      return true;
    } else if (friends_[i] > id) {
      return false;
    }
  }
  return false;
}

unsigned getId() const { return id_; }
std::string getName() const { return name_; }
unsigned getViews() const { return views_; }
unsigned getAge() const { return age_; }