#pragma once
#include <Engine/Sprite.h>

#include "Actor.h"
#include "Direction.h"
#include "Bullet.h"

#include <string>
#include <vector>

namespace ASGE
{
	class Sprite;
	class Renderer;
}

class Player : public Actor
{
public:
	Player();
	~Player() = default;

	//sprite related functions
	void loadAvatar(std::shared_ptr<ASGE::Renderer> renderer) override;

	void renderBullets(std::shared_ptr<ASGE::Renderer> renderer);

	//Setters
	void incrementScore();
	void decrementLives();

	//Getters
	int getSpriteSizeX() const;
	int getSpriteSizeY() const;
	int getScore() const;
	int getLives() const;
	std::string getScoreasString() const;
	std::string getLivesAsString() const;
	std::vector<std::unique_ptr<Bullet>> const& getBullets() const;

	void moveLeftRight(Direction direct) override;
	void fire(std::shared_ptr<ASGE::Renderer> renderer);

	bool checkCollision(int cPosX, int cPosY, int cSpriteSizeX, int cSpriteSizeY);

private:
	const int sprite_SizeX = 39;
	const int sprite_SizeY = 24;
	Direction direction = Direction::NONE;
	int score = 0;
	std::vector<std::unique_ptr<Bullet>> bulletIndex;
	int lives = 3;
};
