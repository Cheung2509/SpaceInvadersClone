#pragma once
#pragma once
#include <memory>

namespace ASGE
{
	class Renderer;
}

class Panel
{
public:
	Panel() = default;
	virtual ~Panel() = default;

	virtual void render(std::shared_ptr<ASGE::Renderer> render) = 0;

	//Getters
	int getPosX() const;
	int getPosY() const;

	//Setters
	void setPosX(int x);
	void setPosY(int y);


private:
	int posX = 0;
	int posY = 0;
};