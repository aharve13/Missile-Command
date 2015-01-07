#include "incoming.h"
#include "testincoming.h"
#include <iostream>
#include <vector>

static int ttg[] = {12000, 10000, 8000, 6000};

Incoming::Incoming(double destination, int difficulty):
    at_dest(false), invalid(false),
    xstart((double) (rand() % 100 + 1) / 100), ystart(0),
    xend(destination), yend(1),
    xcurrent(xstart), ycurrent(ystart), time_to_ground(ttg[difficulty]),
    time_elapsed(0)
{
}

Incoming::~Incoming()
{
}

double Incoming::getX() {
    return xcurrent;
}
double Incoming::getY() {
    return ycurrent;
}
double Incoming::getXstart() {
    return xstart;
}
double Incoming::getYstart() {
    return ystart;
}
double Incoming::getXend() {
    return xend;
}
double Incoming::getYend() {
    return yend;
}
bool Incoming::atDest() {
    return at_dest;
}
bool Incoming::is_invalid() {
    return invalid;
}
void Incoming::invalidate() {
    invalid = true;
}

void Incoming::update_position(int time_passed)
{
    time_elapsed += time_passed;
    if (time_elapsed > time_to_ground) {
        time_elapsed = time_to_ground;
        xcurrent = xend; ycurrent = yend;
        at_dest = true;
    } else {
        xcurrent = (xstart + (xend-xstart)*((double) time_elapsed/time_to_ground));
        ycurrent = (ystart + (yend-ystart)*((double) time_elapsed/time_to_ground));
    }
}
