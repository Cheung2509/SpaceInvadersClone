#include "GameObject.h"

bool GameObject::getIsProjectile() const
{
	return isProjectile;
}

void GameObject::setIsProjectile(bool ip)
{
	isProjectile = ip;
}