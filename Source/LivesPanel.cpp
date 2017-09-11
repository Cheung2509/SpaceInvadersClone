#include "LivesPanel.h"
#include "Player.h"

#include <string>
#include <stdio.h>
#include <Engine/Renderer.h>

LivesPanel::~LivesPanel()
{

}

void LivesPanel::init(Player* player)
{
	player_ptr = player;

	return;
}

void LivesPanel::render(std::shared_ptr<ASGE::Renderer> renderer)
{
	renderer->setFont(0);

	renderer->renderText(("Lives: " + player_ptr->getLivesAsString()).c_str(), getPosX(), getPosY(), ASGE::COLOURS::WHITE);
}