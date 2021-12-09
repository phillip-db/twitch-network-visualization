#pragma once
#include <string>
#include <vector>

/** Object representing a Twitch streamer node with its connecting edges. */
class Streamer {
 public:
  /** Empty default constructor */
  Streamer();

  /**
   * Creates a Streamer object without any friends
   *
   * @param id Id of the Streamer.
   * @param name The Streamer's name.
   * @param views Number of views the Streamer has.
   * @param age Days since the Streamer's account was created.
   */
  Streamer(unsigned id, std::string name, unsigned views, unsigned age);

  /**
   * Creates a Streamer object and assigns its friends.
   *
   * @param id Id of the Streamer.
   * @param name The Streamer's name.
   * @param views Number of views the Streamer has.
   * @param age Days since the Streamer's account was created.
   * @param friends Vector of the Streamer object's friends as ids.
   */
  Streamer(unsigned id, std::string name, unsigned views, unsigned age,
           std::vector<unsigned> friends);

  /**
   * Checks if a Streamer is friends with another Streamer.
   *
   * @param id id of the other streamer.
   * @return true if Streamer is friends with other, false otherwise.
   */
  bool isFriend(unsigned id) const;

  unsigned getId() const;
  std::string getName() const;
  unsigned getViews() const;
  unsigned getAge() const;
  std::vector<unsigned> getFriends() const;
  void setFriends(std::vector<unsigned> friends);

 private:
  unsigned id_;
  std::string name_;
  unsigned views_;
  unsigned age_;
  std::vector<unsigned> friends_;
};