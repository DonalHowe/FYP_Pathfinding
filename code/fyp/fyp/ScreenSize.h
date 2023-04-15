#pragma once

// a struct which controls the size of the windows
static struct ScreenSize{

	// variable which controls the height of the window
	static const int M_HEIGHT = 800;

	// variable which controls the width of the window
	static const int M_WIDTH = 800;

};


// enum class which controls whether the application is in play or testing mode
// play mode = can choose the start and endpoints as well as where each wall is placed
// testing mode = everthing is random from the number of walls placed to the chosen start and end points 

static enum class Mode {

	PLAY,
	TESTING 
};