#pragma once
#include <Engine/OGLGame.h>
#include <string>
#include <memory>
#include <vector>

class Player;
class Enemy;
class EnemyIndex;
class Timer;
class Panel;

struct GameFont;

/**
*  Invaders Game. An OpenGL Game based on ASGE.
*/

enum  class GameState
{
	MAIN_MENU = 0,
	PLAYING = 1,
	GAME_OVER = 2,
	EXIT = 3
};

class InvadersGame:
	public ASGE::OGLGame
{
public:
	InvadersGame();
	~InvadersGame();

	// Inherited via Game
	virtual bool run() override;
	bool shouldExit() const;


	// Inherited via OGLGame
	virtual bool init();
	virtual void drawFrame();

	//Update Functions
	void updateMenu();
	void updateGame();
	void updateGameOver();

	//State Input Function
	void stateInput(int key, int action);

private:
	void processGameActions();
	void processPlayerActions();
	void processEnemyActions();
	void input(int key, int action) const;

	int  state_callback_id = -1;							/**< Input Callback ID. The callback ID assigned by the game engine. */
	int game_callback_id = -1;
	bool exit = false;										/**< Exit boolean. If true the game loop will exit. */
	std::unique_ptr<Player> player_one = nullptr;			/**< Player Object. This will hold information about the player*/
	std::unique_ptr<EnemyIndex> enemyIndex = nullptr;		/**< Enemy Object. This will hold an index of all the enemies with in the game*/
	std::unique_ptr<Timer> timer = nullptr;					/**< Timer. This class will hold all the timings needed within the game*/
	GameState game_state = GameState::MAIN_MENU;			/** Game State. This will determine the state the game is in*/
	std::unique_ptr<Panel> panels[2];
};