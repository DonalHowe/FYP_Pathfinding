#include "JumpPointSearch.h"
/// author : donal Howe
/// 


// returns the timer for the algorithms completion
sf::Time& JumpPointSearch::getTimer()
{
    return m_JumpPointtimer;
}

// returns the termination condition
bool& JumpPointSearch::getIfDone()
{
    return m_JumpPointSearchDone;
}

// default constructor
JumpPointSearch::JumpPointSearch()
{
}

// default destructor
JumpPointSearch::~JumpPointSearch()
{
}
