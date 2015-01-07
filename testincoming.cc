#include "testincoming.h"				//Include the game area header
#include <cmath>					//Include the cmath header (for the position stuff!)
#include <gtkmm/main.h>					//Include the main gtk header
#include <gtkmm/window.h>				//Include the gtk window header
#include <glibmm/main.h>				//Include the glibmm main header
#include <iostream>
#include <chrono>

#define NUMBER_OF_BASES 3				//The total number of bases
#define NUMBER_OF_CITIES 6				//The total number of cities
#define INITIAL_NUMBER_OF_INCOMING 5			//The total number to be fired in a round

int bonus_points = 0;
int level_complete_counter = 0;
int dif = 1; 

static int initinc[] = {3, 5, 7, 9};
static int prob[] = {30, 25, 15, 10};
static int incoming_per_round[] = {20, 30, 40, 50};
//difficulty also affects incoming speed (passed as param)

IncomingTest::IncomingTest(): total_incoming(0), difficulty(dif), score(0), paused(true), previous_time(std::chrono::system_clock::now()), game_over(false), level(1)		//The constructor!
{
  base_existence = {true, true, true};			//The bases exist
  base_location = {0.1, 0.5, 0.9};			//The bases exist at those locations
  city_existence = {true, true, true, true, true, true};//The cities exist
  city_location = {0.2, 0.3, 0.4, 0.6, 0.7, 0.8};	//The cities exist at those locations
  Glib::signal_timeout().connect(sigc::mem_fun(*this, &IncomingTest::on_timeout), 40);
  	//This connects the timeout signal to the incoming test

#ifndef GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED		//This defines and connects the drawing space
  signal_draw().connect(sigc::mem_fun(*this, &IncomingTest::on_draw), false);
#endif

}

IncomingTest::~IncomingTest()				//The destructor!
{
}

void IncomingTest::ground_collision_check(Incoming & m)	//This checks if an incoming has hit the ground
{
  if (m.atDest() && !m.is_invalid())
	//If an incoming is at its destination (should be the ground) and isn't invalid (hit)
    {
      for (int i = 0; i < NUMBER_OF_BASES; i++)		//For all of the bases
	{
	  if (base_location[i] == m.getXend())		//If the base is at the incoming object's destination
	    {
	      base_existence[i] = false;		//The base is no more!
	    }
	}
      for (int i = 0; i < NUMBER_OF_CITIES; i++)	//For all of the cities
	{
	  if (city_location[i] == m.getXend())		//If the city is at the incoming object's destination
	    {
	      city_existence[i] = false;		//The city is no more!
	    }
	}
    }
}

bool IncomingTest::on_draw(const Cairo::RefPtr < Cairo::Context > &cr)	//The actual Cairo drawing area
{
current_time = std::chrono::system_clock::now();
if (paused)
{
elapsed_time = 0;
}
else
{
elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(current_time-previous_time).count();
}
previous_time = current_time;

if (level_complete_counter > 0) {
  Gtk::Allocation allocation = get_allocation();	//Gets the widget area allocation
  const int width = allocation.get_width();		//The widget area width!
  const int height = allocation.get_height();		//The widget area height!
  cr->scale(width, height);				//Scale the drawing area to the actual area
  cr->save();
  cr->set_source_rgb(0, .6, 0);
  Pango::FontDescription font;
  font.set_family("Monospace");
  font.set_weight(Pango::WEIGHT_BOLD);
  font.set_size(50);
  Glib::RefPtr<Pango::Layout> layout3 = create_pango_layout("LEVEL COMPLETE");
  Glib::RefPtr<Pango::Layout> layout4 = create_pango_layout("BONUS POINTS: " + std::to_string(bonus_points));
  layout3->set_font_description(font);
  font.set_size(30);
  layout4->set_font_description(font);
  cr->move_to(.1, .5);
  layout3->show_in_cairo_context(cr);
  cr->move_to(.2, .6);
  layout4->show_in_cairo_context(cr);
  cr->restore();
    level_complete_counter--;
    outgoing_objects.clear();
    outgoing_temp.clear();
    return true;
}

  int location;						//This is a random incoming destination (city or base)
  double destination;					//This is the actual y-coordinates of the destination
  bool loc_found = false;				//Whether a location is actually found
  bool all_gone = true;					//Whether all the locations are gone (defaults to yes)

  Gtk::Allocation allocation = get_allocation();	//Gets the widget area allocation
  const int width = allocation.get_width();		//The widget area width!
  const int height = allocation.get_height();		//The widget area height!
  cr->set_line_width(.004);				//Set the line width to 0.004 (for incoming)
  cr->set_line_cap(Cairo::LINE_CAP_ROUND);            //Set the ends of the lines to round
  cr->set_source_rgb(.9, 0, 0);				//Set the line color to red (for incoming)
  cr->scale(width, height);				//Scale the drawing area to the actual area
  cr->save();						//Save these settings

  cr->save();
  cr->set_source_rgb(0, 0, .6);
  Pango::FontDescription font;
  font.set_family("Monospace");
  font.set_weight(Pango::WEIGHT_NORMAL);
  font.set_size(20);
  Glib::RefPtr<Pango::Layout> layout = create_pango_layout(get_score());
if (!game_over)
{
  Glib::RefPtr<Pango::Layout> layout2 = create_pango_layout(get_level());
  layout2->set_font_description(font);
  cr->move_to(.05, .08);
  layout2->show_in_cairo_context(cr);
}
  layout->set_font_description(font);
  cr->move_to(.05, .05);
  layout->show_in_cairo_context(cr);
  cr->restore();

  if ((std::find(base_existence.begin(), base_existence.end(), true)) == base_existence.end() && (std::find(city_existence.begin(), city_existence.end(), true)) == city_existence.end())
	//If there are no bases or cities left, you lose
    {
game_over = true;
      cr->set_line_width(.05);				//Set the line width to extra-funky
      cr->move_to(0.1, 0.1);				//And write the word "LOSE"
      cr->line_to(0.1, 0.9);
      cr->line_to(0.2, 0.9);
      cr->move_to(0.4, 0.1);
      cr->line_to(0.5, 0.5);
      cr->line_to(0.4, 0.9);
      cr->move_to(0.4, 0.9);
      cr->line_to(0.3, 0.5);
      cr->line_to(0.4, 0.1);
      cr->move_to(0.7, 0.1);
      cr->line_to(0.6, 0.1);
      cr->line_to(0.6, 0.5);
      cr->line_to(0.7, 0.5);
      cr->line_to(0.7, 0.9);
      cr->line_to(0.6, 0.9);
      cr->move_to(0.9, 0.1);
      cr->line_to(0.8, 0.1);
      cr->line_to(0.8, 0.5);
      cr->line_to(0.9, 0.5);
      cr->move_to(0.8, 0.5);
      cr->line_to(0.8, 0.9);
      cr->line_to(0.9, 0.9);
      cr->stroke();					//Actually write the lines
      cr->restore();					//Go back to the saved settings
      return true;					//Don't do anything else in the drawing area
    }

  std::vector < Incoming >::iterator it = incoming_objects.begin();
	//An iterator through the incoming objects

  while (it != incoming_objects.end())			//While the iterator hasn't reached the end
    {
      if ((!(*it).atDest()) && !((*it).is_invalid()))	//If any incoming isn't at the destination or been taken out
	{
	  all_gone = false;				//The incoming objects aren't all gone!
	  break;					//Break the loop
	}
      it++;						//Otherwise, increment through the iterator
    }

  if (all_gone && (total_incoming == incoming_per_round[difficulty]))
	//If the incoming objects are indeed all gone and enough incoming have been created
    {
      level_reset();
      int points_scored = 0;
      for (int i=0; i<NUMBER_OF_CITIES; i++) {
        if (city_existence[i] == true) {
          points_scored += 100;
        }
      }
      add_points(points_scored);
      bonus_points = points_scored;
      cr->restore();					//Go back to the saved settings
      level_complete_counter = 50;
      return true;					//Don't do anything else in the drawing area
    }

	//Now, if you haven't won or lost, we get to the fun stuff.

  if (rand() % prob[difficulty] == 1)					//If you pick the right random number (1/10 chances)
    {
      while (!loc_found)				//While a location has not been found
	{
	  location = rand() % 9;			//Pick a random location
	  if (location < 3)				//If the location is a base
	    {
	      if (base_existence[location] == true)	//If the base exists
		{
		  destination = base_location[location];//Store the base's location
		  loc_found = true;			//A location has been found!
		}
	    }
	  else						//If the location is a city
	    {
	      if (city_existence[location - 3] == true)	//If the city exists
		{
		  destination = city_location[location - 3];	//Store the city's location
		  loc_found = true;			//A location has been found!
		}
	    }
	}
    }
  if (loc_found && (total_incoming < incoming_per_round[difficulty]) && !(paused))
    //If there was a location found and fewer incoming have been created than the limit and not paused
    {
      incoming_objects.push_back(Incoming(destination, difficulty));//Create an incoming object
      total_incoming++;					//Increment the total number of incoming objects created
    }

  std::vector < Incoming >::iterator iter = incoming_objects.begin();
	//An iterator for the incoming_objects vector!

  while (iter != incoming_objects.end())		//While iterating through the entire incoming objects vector
    {
      (*iter).update_position(elapsed_time);			//Update the incoming object position with the time difference
      if (!(*iter).atDest() && !(*iter).is_invalid())	//If the incoming object is not hit and not at its destination
	{
	  cr->move_to((*iter).getXstart(), (*iter).getYstart());	//Go to the incoming object's origin
	  cr->line_to((*iter).getX(), (*iter).getY());		//And draw a line from the origin to the position
	}
      ground_collision_check(*iter);			//Check if the incoming object has hit the ground
      iter++;						//To the next iterator!
    }
  cr->stroke();						//Actually draw all of the lines
  cr->set_source_rgb(0, 0, .9);				//Set the line color to blue (for outgoing objects)

  std::vector < Outgoing >::iterator iter3 = outgoing_temp.begin();

while (iter3 !=outgoing_temp.end())
{
      outgoing_objects.push_back((*iter3));
      iter3++;						//To the next iterator!
}

outgoing_temp.clear();

  std::vector < Outgoing >::iterator iter2 = outgoing_objects.begin();
	//An iterator for the outgoing_objects vector!

  while (iter2 != outgoing_objects.end())		//While iterating through the entire outgoing objects vector
    {
      (*iter2).update_position(elapsed_time);			//Update the outgoing object position with the time difference
      if (!(*iter2).atDest())				//If the outgoing object is not at its destination
	{
if ((*iter2).explosion_phase() == 0)
{
	  cr->move_to((*iter2).getXstart(), (*iter2).getYstart());	//Go to the outgoing object's origin
	  cr->line_to((*iter2).getX(), (*iter2).getY());	//And draw a line from the origin to the position
	  cr->stroke();					//Actually draw the line
}
	  if ((*iter2).explosion_phase() > 0 && (*iter2).explosion_phase() < 5)
	    {
	      cr->save();
	      cr->set_source_rgb(.95, .4, 0);
	      cr->arc((*iter2).getX(), (*iter2).getY(), (.02 * (*iter2).explosion_phase()), 0, 2 * M_PI);
	      check_missile_collision((*iter2).getX(), (*iter2).getY(), (.02 * (*iter2).explosion_phase()), cr);
	      cr->fill();				//Fill in the arc
	      cr->restore();				//Go back to the previous settings
	    }
	  else if ((*iter2).explosion_phase() > 4 && (*iter2).explosion_phase() < 9)
	    {
	      cr->save();
	      cr->set_source_rgb(.85, .85, 0);
	      cr->arc((*iter2).getX(), (*iter2).getY(), (.02 * (9 - (*iter2).explosion_phase())), 0, 2 * M_PI);
	      check_missile_collision((*iter2).getX(), (*iter2).getY(), (.02 * (9 - (*iter2).explosion_phase())), cr);
	      cr->fill();				//Fill in the arc
	      cr->restore();				//Go back to the previous settings
	    }
	}
      iter2++;
    }
  cr->set_source_rgb(0, .9, 0);
  for (size_t i = 0; i < base_existence.size(); i++)
    {
      if (base_existence[i])
	{
	  cr->arc(base_location[i], 1, .05, 0, 2 * M_PI);
	}
    }
  cr->fill();
  cr->set_source_rgb(0, 0, .9);
  for (size_t i = 0; i < city_existence.size(); i++)
    {
      if (city_existence[i])
	{
	  cr->arc(city_location[i], 1, .03, 0, 2 * M_PI);
	}
    }
  cr->fill();
  cr->restore();
  return true;
}

bool IncomingTest::on_timeout()
{
  Glib::RefPtr < Gdk::Window > win = get_window();
  if (win)
    {
      Gdk::Rectangle r(0, 0, get_allocation().get_width(),
		       get_allocation().get_height());
      win->invalidate_rect(r, false);
    }
  return true;
}

void IncomingTest::add_outgoing(double x, double y)
{
  double startpoint = -1;
  if (x < .33)
    {				//try to find the starting location for a missile
      //a redundant (but functional) mess!
      if (base_existence[0])
	startpoint = base_location[0];
      else if (base_existence[1])
	startpoint = base_location[1];
      else if (base_existence[2])
	startpoint = base_location[2];
    }
  else if (x < .66)
    {
      if (base_existence[1])
	startpoint = base_location[1];
      else if (base_existence[0])
	startpoint = base_location[0];
      else if (base_existence[2])
	startpoint = base_location[2];
    }
  else
    {
      if (base_existence[2])
	startpoint = base_location[2];
      else if (base_existence[1])
	startpoint = base_location[1];
      else if (base_existence[0])
	startpoint = base_location[0];
    }
  if (startpoint != -1)
    {
      outgoing_objects.push_back(Outgoing(x, y, startpoint, 1));
    }
}

void IncomingTest::check_missile_collision(double x, double y, double radius, const Cairo::RefPtr < Cairo::Context > &cr)
{
  std::vector < Incoming >::iterator iter = incoming_objects.begin();
  while (iter != incoming_objects.end())
    {
      if (!(*iter).atDest() && !(*iter).is_invalid()) {
	    if (sqrt
	      (((*iter).getX() - x) * ((*iter).getX() - x) +
	       ((*iter).getY() - y) * ((*iter).getY() - y)) < radius) {
	      (*iter).invalidate();
      outgoing_temp.push_back(Outgoing((*iter).getX(), (*iter).getY(), (*iter).getX(), (*iter).getY()));
          add_points(25);
cr->save();
cr->set_source_rgb(1,0,0);
cr->arc(x,y,radius,0,2*M_PI);
cr->fill();
cr->restore();
	    }
	}
      iter++;
    }
}

void IncomingTest::reset(int dif) {
    level = 1;
    score = 0;
    if (difficulty >= 0 && difficulty <= 3) {
        difficulty = dif;
    }
game_over = false;
    incoming_objects.clear();
    outgoing_objects.clear();
    base_existence = {true, true, true};			//The bases exist
    city_existence = {true, true, true, true, true, true};//The cities exist
  int location;						//This is a random incoming destination (city or base)
  double destination;					//This is the actual y-coordinates of the destination
  total_incoming = 0;
  for (int i = 0; i < initinc[difficulty]; i++)	//For some initial number of incoming objects
    {
      location = rand() % 9;				//Choose a random destination
      if (location < 3)					//If a base
	{
	  destination = base_location[location];	//Give the y-coordinates of the base
	}
      else						//If a city
	{
	  destination = city_location[location - 3];	//Give the y-coordinates of the city
	}
      incoming_objects.push_back(Incoming(destination, difficulty));//Creates the incoming objects in the vector
      total_incoming++;					//Increment the total number of incoming so far
    }
}

void IncomingTest::level_reset() {
    level++;
    base_existence = {true, true, true};		//The bases exist
  int location;						//This is a random incoming destination (city or base)
  double destination;					//This is the actual y-coordinates of the destination
    incoming_objects.clear();
    outgoing_objects.clear();
  total_incoming = 0;
  for (int i = 0; i < initinc[difficulty]; i++)	//For some initial number of incoming objects
    {
      location = rand() % 9;				//Choose a random destination
      if (location < 3)					//If a base
	{
	  destination = base_location[location];	//Give the y-coordinates of the base
	}
      else						//If a city
	{
	  destination = city_location[location - 3];	//Give the y-coordinates of the city
	}
      incoming_objects.push_back(Incoming(destination, difficulty));//Creates the incoming objects in the vector
      total_incoming++;					//Increment the total number of incoming so far
    }
}

void IncomingTest::add_points(int points)
{
    score += points;
}

std::string IncomingTest::get_score()
{
    return std::to_string(score);
}

void IncomingTest::setPause(bool pauseState)
{
paused = pauseState;
}

bool IncomingTest::isPaused()
{
return paused;
}

bool IncomingTest::checkGameOver()
{
return game_over;
}
std::string IncomingTest::get_level()
{
  return "Level " + std::to_string(level);
}
