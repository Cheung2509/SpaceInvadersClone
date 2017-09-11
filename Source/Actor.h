#pragma once
#include <Engine/Sprite.h>

#include "GameObject.h"
#include "Direction.h"

namespace ASGE
{
	class Sprite;
	class Renderer;
}

class Actor : public GameObject
{
public:
	Actor() = default;
	~Actor() = default;

	//sprite related functions
	virtual void loadAvatar(std::shared_ptr<ASGE::Renderer> renderer) = 0;
	void renderAvatar(std::shared_ptr<ASGE::Renderer> renderer) const;

	virtual void moveLeftRight(Direction direct) = 0;

	//Setters
	void setIsAlive(bool ia);
	void setXpos(int x);
	void setYpos(int y);

	//Getters
	bool getIsAlive() const;
	int getXpos() const override;
	int getYpos() const override;
	virtual int getSpriteSizeX() const = 0;
	virtual int getSpriteSizeY() const = 0;

protected:
	bool isAlive = true;
	std::unique_ptr<ASGE::Sprite> avatar = nullptr;
};