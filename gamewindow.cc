#include <gtkmm/main.h>				//Include the main gtk header
#include "gtkmm/window.h"			//Include the gtk window header
#include <gtkmm/buttonbox.h>
#include <gtkmm/widget.h>
#include "gamewindow.h"				//Include the game window header
#include "testincoming.h"			//Include the game area header
#include <glibmm/main.h>				//Include the glibmm main header
#include <iostream>

Gamewindow::Gamewindow() : first_time(true)			//The constructor!
{
  inc.setPause(true);
  Glib::signal_timeout().connect(sigc::mem_fun(*this, &Gamewindow::on_timeout), 10);
  	//This connects the timeout signal to the menu test

  set_title("Missile Command");			//Set the window title to something relevant
  set_border_width(0);				//Set the window border to NOTHING
  set_default_size(640,480);			//Set the default window size to 640x480
  quitButton.set_label("Quit");			//Sets the button label to "Quit"
  newGameButton.set_label("New Game");		//Sets the button label to "New Game"
  firstNewGameButton.set_label("New Game");		//Sets the button label to "New Game"
  easyButton.set_label("Easy");			//Sets the button label to "Beginner"
  mediumButton.set_label("Medium");		//Sets the button label to "Intermediate"
  hardButton.set_label("Hard");			//Sets the button label to "Advanced"
  expertButton.set_label("Expert");		//Sets the button label to "Expert"
  pauseButton.set_label("Pause");		//Sets the button label to "Pause"
  resumeButton.set_label("Resume");		//Sets the button label to "Resume"
  quitButton.signal_clicked().connect(sigc::mem_fun(*this, &Gamewindow::quitClick));
	//Connects the signal from the clicked quit button to the quitClick function (in the current member)

  newGameButton.signal_clicked().connect(sigc::mem_fun(*this, &Gamewindow::newGameClick));
	//Connects the signal from the clicked new game button to the newGameClick function (in the current member)

  firstNewGameButton.signal_clicked().connect(sigc::mem_fun(*this, &Gamewindow::firstNewGameClick));
	//Connects the signal from the clicked new game button to the newGameClick function (in the current member)

  easyButton.signal_clicked().connect(sigc::mem_fun(*this, &Gamewindow::easyClick));
	//Connects the signal from the clicked easy button to the easyClick function (in the current member)

  mediumButton.signal_clicked().connect(sigc::mem_fun(*this, &Gamewindow::mediumClick));
	//Connects the signal from the clicked medium button to the mediumClick function (in the current member)

  hardButton.signal_clicked().connect(sigc::mem_fun(*this, &Gamewindow::hardClick));
	//Connects the signal from the clicked hard button to the hardClick function (in the current member)

  expertButton.signal_clicked().connect(sigc::mem_fun(*this, &Gamewindow::expertClick));
	//Connects the signal from the clicked expert button to the expertClick function (in the current member)

  pauseButton.signal_clicked().connect(sigc::mem_fun(*this, &Gamewindow::pauseClick));
	//Connects the signal from the clicked pause button to the pauseClick function (in the current member)

  resumeButton.signal_clicked().connect(sigc::mem_fun(*this, &Gamewindow::resumeClick));
	//Connects the signal from the clicked resume button to the resumeClick function (in the current member)

  add(paned_widget);				//Add the paned widget to the window

  eventbox.set_events(Gdk::BUTTON_PRESS_MASK);	//Sets the eventbox events to button presses
  eventbox.signal_button_press_event().connect(sigc::mem_fun(*this, &Gamewindow::on_eventbox_button_press));
	//Connects the signal from the button press (mouse click on area) to the on_eventbox_button_press function

  eventbox.add(inc);				//Adds the game area to the eventbox

  bbox = Gtk::manage(new Gtk::ButtonBox(Gtk::ORIENTATION_HORIZONTAL));
  bbox->set_border_width(0);
  bbox->set_layout(Gtk::BUTTONBOX_SPREAD);
  bbox->set_spacing(1);

  bbox->add(firstNewGameButton);			//Add the menu button to the window
  bbox->add(quitButton);				//Add the menu button to the window

  paned_widget.pack1(eventbox,true,true);	//Adds the actual game area (in the eventbox) to the window
  paned_widget.pack2(*bbox, false, false);	//Adds the quit button to the window

  show_all_children();				//Shows everything
}

Gamewindow::~Gamewindow()			//The destructor!
{
}

void Gamewindow::quitClick()		//When the button is clicked
{
  Gtk::Main::quit();				//Quits the program entirely
}

void Gamewindow::newGameClick()		//When the button is clicked
{
bbox->add(easyButton);
bbox->add(mediumButton);
bbox->add(hardButton);
bbox->add(expertButton);
bbox->remove(newGameButton);
bbox->remove(resumeButton);
bbox->remove(quitButton);
show_all_children();				//Shows everything
}

void Gamewindow::firstNewGameClick()		//When the button is clicked
{
bbox->add(easyButton);
bbox->add(mediumButton);
bbox->add(hardButton);
bbox->add(expertButton);
bbox->remove(firstNewGameButton);
bbox->remove(quitButton);
show_all_children();				//Shows everything
}

void Gamewindow::easyClick()		//When the button is clicked
{
inc.reset(0);
inc.setPause(false);
first_time = true;
bbox->add(pauseButton);
bbox->remove(easyButton);
bbox->remove(mediumButton);
bbox->remove(hardButton);
bbox->remove(expertButton);
show_all_children();				//Shows everything
}

void Gamewindow::mediumClick()		//When the button is clicked
{
inc.reset(1);
inc.setPause(false);
first_time = true;
bbox->add(pauseButton);
bbox->remove(easyButton);
bbox->remove(mediumButton);
bbox->remove(hardButton);
bbox->remove(expertButton);
show_all_children();				//Shows everything
}

void Gamewindow::hardClick()		//When the button is clicked
{
inc.reset(2);
inc.setPause(false);
first_time = true;
bbox->add(pauseButton);
bbox->remove(easyButton);
bbox->remove(mediumButton);
bbox->remove(hardButton);
bbox->remove(expertButton);
show_all_children();				//Shows everything
}

void Gamewindow::expertClick()		//When the button is clicked
{
inc.reset(3);
inc.setPause(false);
first_time = true;
bbox->add(pauseButton);
bbox->remove(easyButton);
bbox->remove(mediumButton);
bbox->remove(hardButton);
bbox->remove(expertButton);
show_all_children();				//Shows everything
}

void Gamewindow::pauseClick()		//When the button is clicked
{
inc.setPause(true);
bbox->add(newGameButton);
bbox->add(resumeButton);
bbox->add(quitButton);
bbox->remove(pauseButton);
show_all_children();				//Shows everything
}

void Gamewindow::resumeClick()		//When the button is clicked
{
inc.setPause(false);
bbox->add(pauseButton);
bbox->remove(newGameButton);
bbox->remove(resumeButton);
bbox->remove(quitButton);
show_all_children();				//Shows everything
}

bool Gamewindow::on_eventbox_button_press(GdkEventButton* event) {
    double x, y;				//The x and y coordinates of the mouseclick
    Gtk::Allocation allocation = get_allocation();	//Retrieve the allocated space
    const int width = allocation.get_width();	//Retrieve the allocated width
    const int height = allocation.get_height();	//Retrieve the allocated height
    int quit_height, quit_height2;		//The quit button heights
    quitButton.get_preferred_height(quit_height, quit_height2);
	//Retrieves the actual heights of the quit button

    x = (event->x) / width;			//Stores the x-coordinate of the click (normalized to the window)
    y = (event->y) / (height - quit_height);	//Stores the y-coordinate of the click (normalized to the window)
if (!inc.isPaused())
{
    inc.add_outgoing(x,y);			//Passes the click coordinates back to the game area
}
    return true;				//Done!
}

bool Gamewindow::on_timeout()
{
  if (inc.checkGameOver() && first_time)
{
bbox->add(firstNewGameButton);
bbox->add(quitButton);
bbox->remove(pauseButton);
first_time = false;
show_all_children();				//Shows everything
}
  return true;
}
