#include "streamer.h"
#include <algorithm>

Streamer::Streamer() {}
Streamer::Streamer(unsigned id, std::string name, unsigned views, unsigned age)
    : id_(id), name_(name), views_(views), age_(age) {}

Streamer::Streamer(unsigned id, std::string name, unsigned views, unsigned age,
                   std::vector<unsigned> friends)
    : id_(id), name_(name), views_(views), age_(age) {
  std::sort(friends.begin(), friends.end());
  friends_ = friends;
}

void Streamer::setFriends(std::vector<unsigned> friends) { friends_ = friends; }

bool Streamer::isFriend(unsigned id) const {
  for (unsigned i = 0; i < friends_.size(); i++) {
    if (friends_[i] == id) {
      return true;
    } else if (friends_[i] > id) {
      return false;
    }
  }
  return false;
}

unsigned Streamer::getId() const { return id_; }
std::string Streamer::getName() const { return name_; }
unsigned Streamer::getViews() const { return views_; }
unsigned Streamer::getAge() const { return age_; }
std::vector<unsigned> Streamer::getFriends() const { return friends_; }