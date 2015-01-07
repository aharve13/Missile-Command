#include "incoming.h"
#include "testincoming.h"
#include <iostream>
#include <vector>
#include <cmath>

Outgoing::Outgoing(double xend, double yend, double xstart, double ystart):
    at_dest(false), explode_phase(0), xstart(xstart),
    ystart(ystart), xend(xend), yend(yend),
    xcurrent(xstart), ycurrent(ystart),
    time_to_dest(sqrt((xend-xstart)*(xend-xstart) + (yend-ystart)*(yend-ystart))*1000),
    time_elapsed(0)
{
}

Outgoing::~Outgoing()
{
}

double Outgoing::getX() {
    return xcurrent;
}
double Outgoing::getY() {
    return ycurrent;
}
double Outgoing::getXstart() {
    return xstart;
}
double Outgoing::getYstart() {
    return ystart;
}
double Outgoing::getXend() {
    return xend;
}
double Outgoing::getYend() {
    return yend;
}
bool Outgoing::atDest() {
    return at_dest;
}
int Outgoing::explosion_phase() {
    return explode_phase;
}

void Outgoing::update_position(int time_passed)
{
    time_elapsed += time_passed;
    if (time_elapsed > time_to_dest) {
        time_elapsed = time_to_dest;
        xcurrent = xend; ycurrent = yend;
        explode_phase++;
        if (explode_phase > 9) {
            at_dest = true;
        }
    } else {
        xcurrent = (xstart + (xend-xstart)*((double) time_elapsed/time_to_dest));
        ycurrent = (ystart + (yend-ystart)*((double) time_elapsed/time_to_dest));
    }
}
