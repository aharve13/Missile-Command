#ifndef INCOMING_H
#define INCOMING_H

#include <cstdlib>
class Incoming {
  public:
    Incoming(double, int);
    ~Incoming();
    double getXstart();
    double getYstart();
    double getX();
    double getY();
    double getXend();
    double getYend();
    bool atDest();
    bool is_invalid();
    void update_position(int time_passed);
    void invalidate();
  protected:
    bool at_dest;
    bool invalid;
    double xstart;
    double ystart;
    double xend;
    double yend;
    double xcurrent;
    double ycurrent;
    double time_to_ground;
    double time_elapsed;
};
#endif
