#include <Engine/Renderer.h>

#include "Bullet.h"
#include "Actor.h"

Bullet::Bullet(std::shared_ptr<ASGE::Renderer> renderer, Actor* actor)
{
	sprite = renderer->createSprite();
	sprite->loadTexture("..\\..\\Resources\\Textures\\Bullet.png");
	sprite->size[0] = sprite_SizeX;
	sprite->size[1] = sprite_SizeY;
	sprite->position[0] = actor->getXpos() + (actor->getSpriteSizeX() / 2);
	sprite->position[1] = actor->getYpos();
	this->setIsProjectile(true);
}

void Bullet::renderSprite(std::shared_ptr<ASGE::Renderer> renderer) const
{
	sprite->render(renderer);
}

void Bullet::setHit()
{
	hit = true;
}

int Bullet::getXpos() const
{
	return sprite->position[0];
}

int Bullet::getYpos() const
{
	return sprite->position[1];
}

int Bullet::getSpriteSizeX() const
{
	return sprite_SizeX;
}

int Bullet::getSpriteSizeY() const
{
	return sprite_SizeY;
}

bool Bullet::getHit() const
{
	return hit;
}

void Bullet::moveBulletUp() const
{
	sprite->position[1] -= 10;
}

void Bullet::moveBulletDown() const
{
	sprite->position[1] += 10;
}