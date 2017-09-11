#pragma once
#include "Panel.h"

class Player;

class LivesPanel : public Panel
{
public:
	LivesPanel() = default;
	~LivesPanel();

	void init(Player* player);
	virtual void render(std::shared_ptr<ASGE::Renderer> renderer) override;

private:
	Player* player_ptr = nullptr;
};