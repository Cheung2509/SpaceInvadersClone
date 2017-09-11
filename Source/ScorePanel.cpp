#include <string>

#include <Engine/Renderer.h>
#include "ScorePanel.h"
#include <stdio.h>

ScorePanel::~ScorePanel()
{

}

void ScorePanel::init(Player* player)
{
	player_ptr = player;

	return;
}

void ScorePanel::render(std::shared_ptr<ASGE::Renderer> renderer)
{
	renderer->setFont(0);

	renderer->renderText(("Score: " + player_ptr->getScoreasString()).c_str(), getPosX(), getPosY(), ASGE::COLOURS::WHITE);
}