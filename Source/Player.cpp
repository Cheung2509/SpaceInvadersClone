#include "Player.h"

#include <Engine/Renderer.h>

#include <algorithm>

Player::Player()
{
	this->setIsProjectile(false);
}

void Player::loadAvatar(std::shared_ptr<ASGE::Renderer> renderer)
{
	avatar = renderer->createSprite();
	
	if (avatar->loadTexture("..\\..\\Resources\\Textures\\Player.png"))
	{
		avatar->size[0] = 39;
		avatar->size[1] = 24;
		avatar->position[0] = 600;
		avatar->position[1] = 650;
	}
}

void Player::moveLeftRight(Direction direct)
{
	//set direction
	direction = direct;

	//Bounding the player to the screen
	if (avatar->position[0] <= 10)
	{
		this->setXpos(10);
	}
	else if (avatar->position[0] >= 1170)
	{
		this->setXpos(1180);
	}

	//if the player is withing the screen
	if (avatar->position[0] >= 10 && avatar->position[0] <= 1170)
	{
		//move the player left or right
		if (direction == Direction::LEFT)
		{
			this->setXpos(avatar->position[0] - 10);
		}
		else if (direction == Direction::RIGHT)
		{
			this->setXpos(avatar->position[0] + 10);
		}
	}

	//reset the direction of the game
	direction = Direction::NONE;
}


void Player::renderBullets(std::shared_ptr<ASGE::Renderer> renderer)
{
	//If there are bullets fired
	if (!bulletIndex.empty())
	{
		//iterate to all bullets
		for (auto& iter : bulletIndex)
		{
			//Move bullets
			iter->moveBulletUp();
			//render bullets
			iter->renderSprite(renderer);
		}

		const auto new_end = std::remove_if(bulletIndex.begin(), bulletIndex.end(), [](const std::unique_ptr<Bullet>& b)
		{
			return b->getHit() || b->getYpos() == 0;
		});
		bulletIndex.erase(new_end, bulletIndex.end());
	}
}

void Player::fire(std::shared_ptr<ASGE::Renderer> renderer)
{
	bulletIndex.push_back(std::make_unique<Bullet>(renderer, this));
}

bool Player::checkCollision(int cPosX, int cPosY, int cSpriteSizeX, int cSpriteSizeY)
{
	if ((avatar->position[0] + sprite_SizeX) >= cPosX && avatar->position[0] <= (cPosX + cSpriteSizeX) && (avatar->position[1] + sprite_SizeY) >= cPosY && avatar->position[1] <= (cPosY + cSpriteSizeY))
	{
		return true;
	}
	return false;
}

void Player::incrementScore()
{
	++score;
}

void Player::decrementLives()
{
	--lives;
}

int Player::getSpriteSizeX() const
{
	return sprite_SizeX;
}

int Player::getSpriteSizeY() const
{
	return sprite_SizeY;
}

int Player::getScore() const
{
	return score;
}

int Player::getLives() const
{
	return lives;
}

std::string Player::getScoreasString() const
{
	std::string str = std::to_string(score);

	return str;
}

std::string Player::getLivesAsString() const
{
	std::string str = std::to_string(lives);

	return str;
}
std::vector<std::unique_ptr<Bullet>> const& Player::getBullets() const
{
	return bulletIndex;
}