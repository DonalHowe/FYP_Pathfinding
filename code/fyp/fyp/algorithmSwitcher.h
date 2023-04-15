/// author : donal Howe
/// 
/// included libraries and dependencies
/// 

#pragma once
#include <iostream>

/// Which algorithm controls the algorithm which the user chooses to select
/// Astar =  the Astar Search algorithm
/// DstarLite = the Dstar Lite search Algorithm 
/// LPASTAR = the Life long planning Astar search Algorithm 
/// Dikstras =  the Dijkstas search Algorithm 
/// DEPTH = the depth first search search Algorithm 
/// JPS = the jump point search pathfinding algorithm
/// </summary>
static enum class WhichAlgorithm {

	Astar,
	DstarLite,
	LPASTAR,
	DIKSTRAS,
	DEPTH,
	JPS,

};

// GridSize enum class control the size of the grid from small 10x10 sized grid
// large being 50x50 sized grid
// veryLarge being 100x100 sized grid
static enum class GridSize {

	small,
	large,
	veryLarge

};

// Race enum class controls whether you want to see the algorithms race 
// this will race Dstar vs chosen algorithm
// you can see Dstar Lites path chosen compared to the algorithm chosen by the user
static enum class Race {

	yes,
	No
	

};

/// Debug enum class controls the vusual information for Dstar Lite 
//  you can see rhs gcost and key information if this is turned on
/// </summary>
static enum class debug {

	On,
	Off


};

