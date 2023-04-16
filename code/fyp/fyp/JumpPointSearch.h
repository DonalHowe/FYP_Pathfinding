/// author : donal Howe
/// 
/// included libraries and dependencies
/// 

#pragma once
#include<queue>
#include"Cell.h"
#include"Grid.h"
#include<stack>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>


class JumpPointSearch
{
	// private class variables and functions
private:

	// this is the timer used to calculate the time until completion of the algorithm
	sf::Time m_JumpPointtimer;

	// bool to control if the algorithm is done 
	bool m_JumpPointSearchDone = false;

	// public class variables and functions
public:

	// returns the timer
	sf::Time& getTimer();

	//returns the termination condition
	bool& getIfDone();


	// default constructor
	JumpPointSearch();

	// default destrucotor
	~JumpPointSearch();
};

