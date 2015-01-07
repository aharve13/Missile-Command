#ifndef OUTGOING_H
#define OUTGOING_H

#include <cstdlib>
class Outgoing {
  public:
    Outgoing(double xend, double yend, double xstart, double ystart);
    ~Outgoing();
    double getXstart();
    double getYstart();
    double getX();
    double getY();
    double getXend();
    double getYend();
    bool atDest();
    void update_position(int time_passed);
    int explosion_phase();
  protected:
    bool at_dest;
    int explode_phase;
    double xstart;
    double ystart;
    double xend;
    double yend;
    double xcurrent;
    double ycurrent;
    double time_to_dest;
    double time_elapsed;
};
#endif
