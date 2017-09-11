#pragma once
#include "Panel.h"
#include "Player.h"

class Player;

class ScorePanel : public Panel
{
public:
	ScorePanel() = default;
	~ScorePanel();

	void init(Player* player);
	virtual void render(std::shared_ptr<ASGE::Renderer> renderer) override;

private:
	Player* player_ptr = nullptr;
};