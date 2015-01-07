#ifndef TESTINCOMING_H
#define TESTINCOMING_H

#include <gtkmm/drawingarea.h>
#include <gtkmm/eventbox.h>
#include "incoming.h"
#include "outgoing.h"
#include <vector>
#include <chrono>

class Incoming;

class IncomingTest:public Gtk::DrawingArea
{
public:
  IncomingTest();
  virtual ~ IncomingTest();
  void add_outgoing(double, double);
  void reset(int);
  void level_reset();
  void add_points(int);
  std::string get_score();
  void setPause(bool);
  bool isPaused();
  bool checkGameOver();
  std::string get_level();
protected:
  virtual bool on_draw(const Cairo::RefPtr < Cairo::Context > &cr);
  bool on_timeout();
  int total_incoming;
  std::vector < Incoming > incoming_objects;
  std::vector < Outgoing > outgoing_objects;
  std::vector < Outgoing > outgoing_temp;
  std::vector < bool > base_existence;
  std::vector < bool > city_existence;
  std::vector < double > base_location;
  std::vector < double > city_location;
  void ground_collision_check(Incoming &);
  void check_missile_collision(double, double, double, const Cairo::RefPtr < Cairo::Context >&);
  int difficulty;
  int score;
  bool paused;
  int elapsed_time;
  std::chrono::time_point<std::chrono::high_resolution_clock> previous_time;
  std::chrono::time_point<std::chrono::high_resolution_clock> current_time;
  bool game_over;
  int level;
};
#endif
