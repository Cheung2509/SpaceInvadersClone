#pragma once
#include <Engine/Sprite.h>

#include "GameObject.h"

class Actor;

namespace ASGE
{
	class Sprite;
	class Renderer;
}

class Bullet : public GameObject
{
public:
	Bullet(std::shared_ptr<ASGE::Renderer> renderer, Actor* actor);
	~Bullet() = default;

	void renderSprite(std::shared_ptr<ASGE::Renderer> renderer) const;

	void moveBulletUp() const;
	void moveBulletDown() const;

	void setHit();

	int getXpos() const override;
	int getYpos() const override;
	int getSpriteSizeX() const override;
	int getSpriteSizeY() const override;
	bool getHit() const;

private:
	std::unique_ptr<ASGE::Sprite> sprite = nullptr;
	int const sprite_SizeX = 2;
	int const sprite_SizeY = 8;
	bool hit = false;
};