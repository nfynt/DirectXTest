#include "GameOver.h"
#include "System.h"
#include "Graphics.h"
#include "Font.h"
#include "Game.h"

GameOver::GameOver() :
	delay_(0),
	font_(0)
{
}

void GameOver::OnActivate(System *system, StateArgumentMap &args)
{
	delay_ = 120;
	if (font_ == 0)
	{
		font_ = system->GetGraphics()->CreateXFont("Arial", 48);
	}
}

void GameOver::OnUpdate(System *system)
{
	if (--delay_ == 0)
	{
		system->SetNextState("MainMenu");
	}
}

void GameOver::OnRender(System *system)
{
	system->GetGame()->RenderBackgroundOnly(system->GetGraphics());

	const char *gameOverText = "Game Over";
	int textWidth = font_->CalculateTextWidth(gameOverText);
	int textX = (800 - textWidth) / 2;
	int textY = (600 - 48) / 2;
	font_->DrawText(gameOverText, textX, textY, 0xffffff00);
}

void GameOver::OnDeactivate(System *system)
{
	system->GetGraphics()->DestroyXFont(font_);
	font_ = 0;
}
