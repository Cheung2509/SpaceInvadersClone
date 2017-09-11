#include "Actor.h"

void Actor::renderAvatar(std::shared_ptr<ASGE::Renderer> renderer) const
{
	avatar->render(renderer);
}

bool Actor::getIsAlive() const
{
	return isAlive;
}

int Actor::getXpos() const
{
	return avatar->position[0];
}

int Actor::getYpos() const
{
	return avatar->position[1];
}

void Actor::setIsAlive(bool ia)
{
	isAlive = ia;
}

void Actor::setXpos(int x)
{
	avatar->position[0] = x;
}

void Actor::setYpos(int y)
{
	avatar->position[1] = y;
}