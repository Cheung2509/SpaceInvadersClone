#include <Engine/Renderer.h>
#include <time.h>

#include "EnemyIndex.h"
#include "GameObject.h"


void EnemyIndex::loadEnemyAvatar(std::shared_ptr<ASGE::Renderer> renderer)
{
	for (auto& iter : enemies)
	{
		iter->loadAvatar(renderer);
	}
}

void EnemyIndex::addEnemies(std::unique_ptr<Enemy>&& obj)
{
	enemies.push_back(std::move(obj));
}

void EnemyIndex::renderEnemies(std::shared_ptr<ASGE::Renderer> renderer)
{
	for (auto& iter : enemies)
	{
		iter->renderAvatar(renderer);
		iter->renderBullets(renderer);
	}
}

void EnemyIndex::setEnemiesInitPos()
{
	int index = 0;
	int row = 0;
	for (auto& iter : enemies)
	{
		if (index == enemiesInRow)
		{
			index = 0;
			row = row++;
		}

		int posX = ((iter->getSpriteSizeX() + 40) * index) + 160;
		iter->setXpos(posX);

		int posY = ((iter->getSpriteSizeY() + 10) * row) + 50;
		iter->setYpos(posY);

		index++;
	}
}

int EnemyIndex::getEnemiesInRow() const
{
	return enemiesInRow;
}

int EnemyIndex::getInitEnemies() const
{
	return initEnemies;
}
bool EnemyIndex::getHasMoveDown() const
{
	return hasMoveDown;
}

bool EnemyIndex::getEmptyIndex() const
{
	return enemies.empty();
}

std::vector<std::unique_ptr<Enemy>> const& EnemyIndex::getEnemies() const
{
	return enemies;
}

void EnemyIndex::moveEnemies(std::shared_ptr<ASGE::Renderer> renderer)
{
	srand(time(NULL));

	int fire = rand() % enemies.size();

	int index = 0;

	//Determine the direction if the enemy is not moving down
  	for (auto& iter : enemies)
	{
		if (index == fire)
		{
			iter->fire(renderer);
		}

		if (iter->getXpos() <= 40 && hasMoveDown == false)
		{
			direction = Direction::RIGHT;
			moveDown = true;
		}
		else if ((iter->getXpos() + iter->getSpriteSizeX()) >= 1240 && hasMoveDown == false)
		{
			direction = Direction::LEFT;
			moveDown = true;
		}

		++index;
	}

	if ((hasMoveDown == false) && (moveDown == true))
	{
		moveEnemiesDown();
	}
	else
	{
		moveEnemiesLeftRight();
	}
}

void EnemyIndex::moveEnemiesDown()
{
	//Move the enemy
	for (auto& iter : enemies)
	{
		iter->moveEnemyDown();
	}
	hasMoveDown = true;
	moveDown = false;
}

void EnemyIndex::moveEnemiesLeftRight()
{
	//Move the enemy
	for (auto& iter : enemies)
	{
		iter->moveLeftRight(direction);
	}
	hasMoveDown = false;
}

bool EnemyIndex::checkCollision(GameObject* obj)
{
	for (auto& iter : enemies)
	{
		//if any of the enemies collide with the enemy
		if (iter->checkCollision(obj->getXpos(), obj->getYpos(), obj->getSpriteSizeX(), obj->getSpriteSizeY()))
		{
			if (obj->getIsProjectile())
			{
				iter->setIsAlive(false);

			}
		}
	}
	
	return false;
}

