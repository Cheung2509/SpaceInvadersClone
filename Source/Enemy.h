#pragma once
#include "Actor.h"
#include "Actor.h"
#include "Direction.h"
#include "Bullet.h"

#include <Engine/Sprite.h>

#include <memory>
#include <vector>

namespace ASGE
{
	class Sprite;
	class Renderer;
}


class Enemy : public Actor
{
public:
	Enemy();
	~Enemy() = default;

	//sprite related functions
	void loadAvatar(std::shared_ptr<ASGE::Renderer> renderer) override;


	//Getters
	int getSpriteSizeX() const override;
	int getSpriteSizeY() const override;
	std::vector<std::unique_ptr<Bullet>> const& getBullets() const;

	void moveLeftRight(Direction direct) override;
	void moveEnemyDown();

	void fire(std::shared_ptr<ASGE::Renderer> renderer);
	void renderBullets(std::shared_ptr<ASGE::Renderer> renderer);

	bool checkCollision(int cPosX, int cPosY, int cSpriteSizeX, int cSpriteSizeY);
private:
	const int sprite_SizeX = 32;
	const int sprite_SizeY = 32;
	Direction direction = Direction::LEFT;
	std::vector<std::unique_ptr<Bullet>> bullets;
};