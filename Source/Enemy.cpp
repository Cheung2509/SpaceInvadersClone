#include <Engine/Renderer.h>

#include "Enemy.h"

#include <algorithm>

Enemy::Enemy()
{
	this->setIsProjectile(false);
}

//Function to load the objects sprite
void Enemy::loadAvatar(std::shared_ptr<ASGE::Renderer> renderer)
{
	avatar = renderer->createSprite();
	avatar->loadTexture("..\\..\\Resources\\Textures\\Top_Alien_1.png");
	avatar->size[0] = 32;
	avatar->size[1] = 32;
	avatar->position[0] = 20;
	avatar->position[1] = 20;
}

int Enemy::getSpriteSizeX() const
{
	return sprite_SizeX;
}

int Enemy::getSpriteSizeY() const
{
	return sprite_SizeY;
}

std::vector<std::unique_ptr<Bullet>> const& Enemy::getBullets() const
{
	return bullets;
}

void Enemy::moveLeftRight(Direction direct)
{
	//Setting the direction of the aliens will move
	direction = direct;


	//Move the enemy according to the direction
	if (direction == Direction::LEFT)
	{
		this->setXpos(avatar->position[0] - sprite_SizeX + 10);
	}
	else if (direction == Direction::RIGHT)
	{
		this->setXpos(avatar->position[0] + sprite_SizeX + 10);
	}
}

void Enemy::moveEnemyDown()
{	
	this->setYpos(avatar->position[1] + sprite_SizeY + 10);
}

bool Enemy::checkCollision(int cPosX, int cPosY, int cSpriteSizeX, int cSpriteSizeY)
{
	if ((avatar->position[0] + sprite_SizeX) >= cPosX && avatar->position[0] <= (cPosX + cSpriteSizeX) && (avatar->position[1] + sprite_SizeY) >= cPosY && avatar->position[1] <= (cPosY + cSpriteSizeY))
	{
		return true;
	}
	return false;
}

void Enemy::fire(std::shared_ptr<ASGE::Renderer> renderer)
{
	bullets.push_back(std::make_unique<Bullet>(renderer, this));
}

void Enemy::renderBullets(std::shared_ptr<ASGE::Renderer> renderer)
{
	//If there are bullets fired
	if (!bullets.empty())
	{
		//iterate to all bullets
		for (auto& iter :bullets)
		{
			//Move bullets
			iter->moveBulletDown();
			//render bullets
			iter->renderSprite(renderer);
		}

		const auto new_end = std::remove_if(bullets.begin(), bullets.end(), [](const std::unique_ptr<Bullet>& b)
		{
			return b->getHit() || b->getYpos() == 0;
		});
		bullets.erase(new_end, bullets.end());
	}
}