#pragma once

class GameObject
{
public:
	GameObject() = default;
	virtual ~GameObject() = default;

	virtual int getXpos() const = 0;
	virtual int getYpos() const = 0;
	virtual int getSpriteSizeX() const = 0;
	virtual int getSpriteSizeY() const = 0;
	virtual bool getIsProjectile() const;

	void setIsProjectile(bool ip);
private:
	bool isProjectile;
};