#include <gtkmm/main.h>			//Only include the main gtk header (no need for everything here)
#include "gamewindow.h"			//Include the game window header
#include <ctime>			//Include the ctime header (for seeding the random library)
#include <cstdlib>			//Include the cstdlib header (for the srand function)

int main(int argc, char *argv[])	//The main function (with command-line arguments)
{
  srand(time(NULL));			//Seed the random number generator with the current time
  Gtk::Main kit(argc, argv);		//Creates a Main object, passing command-line arguments

  Gamewindow game_window;		//Creates a window using the gamewindow class
  Gtk::Main::run(game_window);		//Shows the main window and returns when it is closed.

  return EXIT_SUCCESS;			//Woo! Done.
}
