#ifndef GAMEWINDOW_H			//This header file creates the Gamewindow class
#define GAMEWINDOW_H

#include <gtkmm/window.h>		//Only need the GTK window header
#include <gtkmm/paned.h>		//Include the Paned header
#include <gtkmm/button.h>		//Only need the GTK window header
#include <gtkmm/buttonbox.h>		//Only need the GTK window header

#include "testincoming.h"

class Gamewindow : public Gtk::Window	//Create a Gamewindow inherited from a GTK window
{
public:					//These are public variable/functions (all can see)
  Gamewindow();				//The constructor function
  virtual ~Gamewindow();		//The destructor function (virtual because Gamewindow is derived)

protected:				//These are protected variables/functions (only this/children can see)
  void quitClick();			//Handles when the button is clicked
  void newGameClick();			//Handles when the button is clicked
  void firstNewGameClick();		//Handles when the button is clicked
  void easyClick();			//Handles when the button is clicked
  void mediumClick();			//Handles when the button is clicked
  void hardClick();			//Handles when the button is clicked
  void expertClick();			//Handles when the button is clicked
  void pauseClick();			//Handles when the button is clicked
  void resumeClick();			//Handles when the button is clicked
  bool on_timeout();

  bool first_time;

  Gtk::Button newGameButton;		//Creates a new child widget of type GTK button called newGameButton
  Gtk::Button firstNewGameButton;	//Creates a new child widget of type GTK button called newGameButton
  Gtk::Button quitButton;		//Creates a new child widget of type GTK button called quitButton
  Gtk::Button easyButton;		//Creates a new child widget of type GTK button called newGameButton
  Gtk::Button mediumButton;		//Creates a new child widget of type GTK button called quitButton
  Gtk::Button hardButton;		//Creates a new child widget of type GTK button called newGameButton
  Gtk::Button expertButton;		//Creates a new child widget of type GTK button called quitButton
  Gtk::Button pauseButton;		//Creates a new child widget of type GTK button called newGameButton
  Gtk::Button resumeButton;		//Creates a new child widget of type GTK button called newGameButton

  Gtk::VPaned paned_widget;		//Creates the vertical panes widget
  IncomingTest inc;			//Creates the Incoming object
  Gtk::EventBox eventbox;
  bool on_eventbox_button_press(GdkEventButton*);
  Gtk::ButtonBox* bbox;
};

#endif
