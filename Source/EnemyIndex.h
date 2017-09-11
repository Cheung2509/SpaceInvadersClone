#pragma once
#include <vector>
#include <memory>

#include "Enemy.h"

class GameObject;

namespace ASGE
{
	class Renderer;
}

class EnemyIndex
{
public:
	EnemyIndex() = default;
	~EnemyIndex() = default;

	void addEnemies(std::unique_ptr<Enemy>&&);
	void renderEnemies(std::shared_ptr<ASGE::Renderer> renderer);
	void loadEnemyAvatar(std::shared_ptr<ASGE::Renderer> renderer);

	//Setters
	void setEnemiesInitPos();
	//Getters
	int getEnemiesInRow() const;
	int getInitEnemies() const;
	bool getHasMoveDown() const;
	bool getEmptyIndex() const;
	std::vector<std::unique_ptr<Enemy>> const& getEnemies() const;

	void moveEnemies(std::shared_ptr<ASGE::Renderer> renderer);
	void moveEnemiesDown();
	void moveEnemiesLeftRight();

	bool checkCollision(GameObject* obj);
private:
	std::vector<std::unique_ptr<Enemy>> enemies;
	int const initEnemies = 54 ;
	int const enemiesInRow = 11;
	Direction direction = Direction::LEFT;
	bool hasMoveDown = false;
	bool moveDown = false;
};