#include "LevelStart.h"
#include "System.h"
#include "Graphics.h"
#include "Font.h"
#include "Game.h"

LevelStart::LevelStart() :
	level_(0),
	delay_(0),
	font_(0)
{
}

void LevelStart::OnActivate(System *system, StateArgumentMap &args)
{
	level_ = args["Level"].asInt;
	delay_ = 120;

	if (font_ == 0)
	{
		font_ = system->GetGraphics()->CreateXFont("Arial", 48);
	}
}

void LevelStart::OnUpdate(System *system)
{
	if (--delay_ == 0)
	{
		GameState::StateArgumentMap args;
		args["Level"].asInt = level_;
		system->SetNextState("PlayingState", args);
	}
}

void LevelStart::OnRender(System *system)
{
	system->GetGame()->RenderBackgroundOnly(system->GetGraphics());

	char levelStartText[256];
	sprintf_s(levelStartText, "Level %d", level_);
	int textWidth = font_->CalculateTextWidth(levelStartText);
	int textX = (800 - textWidth) / 2;
	int textY = (600 - 48) / 2;
	font_->DrawText(levelStartText, textX, textY, 0xffffff00);
}

void LevelStart::OnDeactivate(System *system)
{
	system->GetGraphics()->DestroyXFont(font_);
	font_ = 0;
}
