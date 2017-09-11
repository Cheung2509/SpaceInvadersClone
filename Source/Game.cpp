#include "Game.h"
#include "Actions.h"
#include "Constants.h"
#include "GameFont.h"
#include "Player.h"
#include "Enemy.h"
#include "EnemyIndex.h"
#include "Timer.h"
#include "Bullet.h"
#include "ScorePanel.h"
#include "Panel.h"
#include "LivesPanel.h"

#include <Engine/Input.h>
#include <Engine/Keys.h>
#include <Engine/Sprite.h>

/**
*   @brief   Default Constructor.
*/
InvadersGame::InvadersGame()
{

}


/**
*   @brief   Destructor.
*   @details Remove any non-managed memory and callbacks.
*/
InvadersGame::~InvadersGame()
{

}


/**
*   @brief   Initialises the game.
*   @details The game window is created and all assets required to
			 run the game are loaded. The input callback should also
			 be set in the initialise function. 
*   @return  True if the game initialised correctly.
*/
bool InvadersGame::init()
{
	width = WINDOW_WIDTH;
	height = WINDOW_HEIGHT;
	if (!initAPI())
	{
		return false;
	}

	renderer->setWindowTitle("Invaders - Exercise 1");
	renderer->setClearColour(ASGE::COLOURS::BLACK);
	toggleFPS();
	
	//Initializing the player
	player_one = std::make_unique<Player>();
	player_one->loadAvatar(renderer);

	//Initializing the first wave of enemies
	enemyIndex = std::make_unique<EnemyIndex>();
	for (int i = 0; i <= enemyIndex->getInitEnemies(); i++)
	{
		enemyIndex->addEnemies(std::make_unique<Enemy>());
	}

	enemyIndex->loadEnemyAvatar(renderer);
	enemyIndex->setEnemiesInitPos();

	//Initialize timer
	timer = std::make_unique<Timer>();

	// input callback function
	state_callback_id = this->inputs->addCallbackFnc(&InvadersGame::stateInput, this);
	
	// load fonts we need
	GameFont::fonts[0] = new GameFont(
		renderer->loadFont("..\\..\\Resources\\Fonts\\Comic.ttf", 42), "default", 42);
	
	std::unique_ptr<ScorePanel> scorePanel = std::make_unique<ScorePanel>();
	scorePanel->init(player_one.get());
	scorePanel->setPosX(20);
	scorePanel->setPosY(45);

	std::unique_ptr<LivesPanel> livesPanel = std::make_unique<LivesPanel>();
	livesPanel->init(player_one.get());
	livesPanel->setPosX(1120);
	livesPanel->setPosY(45);

	panels[0] = std::move(scorePanel);
	panels[1] = std::move(livesPanel);

	if (GameFont::fonts[0]->id == -1)
	{
		return false;
	}

	return true;
}


/**
*   @brief   The main game loop. 
*   @details The main loop should be responsible for updating the game
			 and rendering the current scene. Runs until the shouldExit
			 signal is received.
*   @return  True if the game ran correctly. 
*/
bool InvadersGame::run()
{
	while (!shouldExit())
	{
		if (game_state == GameState::MAIN_MENU)
		{
			updateMenu();
		}
		else if (game_state == GameState::PLAYING)
		{
			updateGame();
		}
		else if (game_state == GameState::GAME_OVER)
		{
			updateGameOver();
		}
	}

	return true;
}


/**
*   @brief   Should the game exit?
*   @details Has the renderer terminated or the game requesting to exit?
*   @return  True if the game should exit
*/
bool InvadersGame::shouldExit() const
{
	return (renderer->exit() || this->exit);
}

void InvadersGame::drawFrame()
{
	//If statement to check the game state
	if (game_state == GameState::MAIN_MENU)
	{
		//Render Main menu text; 
		renderer->setFont(GameFont::fonts[0]->id);
		renderer->renderText("Space Invaders\n Press any key to start", 375, 325, 1.0, ASGE::COLOURS::PURPLE);
	}
	else if (game_state == GameState::PLAYING)
	{
		//Render the games avatars
		player_one->renderAvatar(renderer);
		player_one->renderBullets(renderer);
		enemyIndex->renderEnemies(renderer);

		for (auto& panel : panels)
		{
			panel->render(renderer);
		}
	}
	else if (game_state == GameState::GAME_OVER)
	{
		//Render end screen text
		renderer->setFont(GameFont::fonts[0]->id);
		renderer->renderText(("You Died\n Your Scor was: " + player_one->getScoreasString()).c_str(), 375, 325, 1.0, ASGE::COLOURS::PURPLE);
	}
}

/**
*	@brief Updating menu every frame
*	@details To render the menu when game_state is at MAINMENU
*	@return void
*/
void InvadersGame::updateMenu()
{
	//Begin to render frame
	beginFrame();

	//Draw the onto the window
	drawFrame();

	//End the frame
	endFrame();
}

/**
*	@brief Updating Game every frame
*	@details To render the game when game_state is at PLAYING
*	@return void
*/
void InvadersGame::updateGame()
{
	//Begin to render frame
	beginFrame();

	processGameActions();

	//Draw the onto the window
	drawFrame();

	//End the frame
	endFrame();
}


void InvadersGame::updateGameOver()
{
	//Begin to render frame
	beginFrame();

	//Draw the onto the window
	drawFrame();

	//End the frame
	endFrame();
}

/**
*   @brief   Processes any key inputs and translates them to a GameAction
*   @details This function is added as a callback to handle the game's 
			 input. Key presseses are translated in to GameActions which 
			 are then processed by the main game loop.
*   @param   key is the key the action relates to
*   @param   action whether the key was released or pressed
*   @return  void
*/
void InvadersGame::input(int key, int action) const
{
	//if a key is pressed and the game state is on PLAYING
	if (action = ASGE::KEYS::KEY_REPEATED && game_state == GameState::PLAYING)
	{
		//If the escape key is pressed
		if (key == ASGE::KEYS::KEY_ESCAPE)
		{
			//set game actiont to exit the game
			game_action = GameAction::EXIT;
		}
		else if (key == ASGE::KEYS::KEY_A)	//if the A key is pressed
		{
			//set game action to move the player left
			game_action = GameAction::LEFT;
		}
		else if (key == ASGE::KEYS::KEY_D)
		{
			game_action = GameAction::RIGHT;
		}
		else if (action = ASGE::KEYS::KEY_PRESSED && game_state == GameState::PLAYING)
		{
			if (key == ASGE::KEYS::KEY_SPACE)
			{
				game_action = GameAction::FIRE;
			}
		}
	}                   
}

/**
*	@brief updating the state of the game
*	@details To update the state of the game
*   @param   key is the key the action relates to
*   @param   action whether the key was released or pressed
*	@return void
*/
void InvadersGame::stateInput(int key, int action)
{
	//if a any button is pressed
	if (action == ASGE::KEYS::KEY_PRESSED && game_state == GameState::MAIN_MENU)
	{
		//change the game state to PLAYING
		game_state = GameState::PLAYING;

		//Start the game timer
		timer->beginTimer();

		//Change input
		game_callback_id = this->inputs->addCallbackFnc(&InvadersGame::input, this);
	}
}

/**
*   @brief   Processes the next game action
*   @details Uses the game action that was a direct result of 
*            user input. It allows input to processed in a different
             thread and the game actions performed in the main thread. 
*   @return  void
*/
void InvadersGame::processGameActions()
{
	processPlayerActions();
	processEnemyActions();
}

void InvadersGame::processPlayerActions()
{
	//If the player is Alive
	if (player_one->getIsAlive() == false || player_one->getLives() == 0)
	{
		//End the timer
		timer->getEndTimer();

		//If the player dies set the game state to Game Over
		game_state = GameState::GAME_OVER;
	}
	else
	{
		if (game_action == GameAction::EXIT)
		{
			//Exut the game
			this->exit = true;
		}
		else if (game_action == GameAction::FIRE)
		{
			player_one.get()->fire(renderer);
		}
		else if (game_action == GameAction::LEFT)
		{
			//Move the player to the left
			player_one->moveLeftRight(Direction::LEFT);
		}
		else if (game_action == GameAction::RIGHT)
		{
			//Move the player to the right
			player_one->moveLeftRight(Direction::RIGHT);
		}
	}

	for (auto& iterator = enemyIndex.get()->getEnemies().begin(); iterator != enemyIndex.get()->getEnemies().end(); ++iterator)
	{
		for (auto& iter = iterator->get()->getBullets().begin(); iter != iterator->get()->getBullets().end(); ++iter)
		{
			if (player_one->checkCollision(iter->get()->getXpos(), iter->get()->getYpos(), iter->get()->getSpriteSizeX(), iter->get()->getSpriteSizeY()))
			{
				player_one->decrementLives();
				iter->get()->setHit();
			}
		}
	}

	game_action = GameAction::NONE;
}

void InvadersGame::processEnemyActions()
{
	//Setting and starting intervals depending on whether the enemies can move
	if (timer->getIntervalReset())
	{
		timer.get()->setStartInterval();
		timer.get()->setIntervalReset(false);
	}
	else
	{
		//Set the current interval time
		timer.get()->setEndInterval();
	}

	//Set the interval time
	timer.get()->setInterval();

	//Set the enemies to move once the interval is 2 seconds
 	if (timer.get()->getInterval() >= timer->getTime())
	{
		//Move the enemies
		enemyIndex.get()->moveEnemies(renderer);

		//Reset the interval timer
		timer.get()->setIntervalReset(true);
	}

	//check if enemy collides with player
	if (enemyIndex.get()->checkCollision(player_one.get()))
	{
		//if player collided with one enemy, player dies
		player_one.get()->setIsAlive(false);
	}

	for (auto& iter = player_one.get()->getBullets().begin(); iter != player_one.get()->getBullets().end(); ++iter)
	{
		if (enemyIndex.get()->checkCollision(iter->get()))
		{
			player_one->incrementScore();
			iter->get()->setHit();
		}
	}

	if (enemyIndex.get()->getEmptyIndex())
	{
		for (int i = 0; i <= enemyIndex->getInitEnemies(); i++)
		{
			enemyIndex->addEnemies(std::make_unique<Enemy>());
		}

		enemyIndex->loadEnemyAvatar(renderer);
		enemyIndex->setEnemiesInitPos();

		timer.get()->decrementTime();
	}
}