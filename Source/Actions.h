#pragma once
#include <string>
#include <atomic>

/** @file Actions.h
    @brief   Actions file defines a thread safe game action
    @details GameActions are stored here as well as a thread safe  
             GameAction variable, which has external linkage. 
*/


/** @enum GameAction
*   @brief is a strongly typed enum class representing the next game action
*/
enum class GameAction
{
	INVALID = -1,  /**< is a non-valid game action */
	NONE    =  0,  /**< means no outstanding action to process */
	START,
	EXIT,          /**< signals the intention to exit the game */
	LEFT,
	RIGHT,
	FIRE
};

extern std::atomic<GameAction> game_action;