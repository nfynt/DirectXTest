#include "MainMenu.h"
#include "System.h"
#include "Graphics.h"
#include "Game.h"
#include "Font.h"
#include "Keyboard.h"

MainMenu::MainMenu() :
	titleFont_(0),
	optionsFont_(0)
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::OnActivate(System *system, StateArgumentMap &args)
{
	if (titleFont_ == 0)
	{
		titleFont_ = system->GetGraphics()->CreateXFont("Arial", 48);
		optionsFont_ = system->GetGraphics()->CreateXFont("Arial", 16);
	}
}

void MainMenu::OnUpdate(System *system)
{
	Keyboard *keyboard = system->GetKeyboard();
	if (keyboard->IsKeyPressed(VK_SPACE))
	{
		GameState::StateArgumentMap args;
		args["Level"].asInt = 1;
		system->SetNextState("LevelStart", args);
	}
}

void MainMenu::OnRender(System *system)
{
	system->GetGame()->RenderBackgroundOnly(system->GetGraphics());
	titleFont_->DrawText("ASTEROIDS", 50, 50, 0xffffff00);
	optionsFont_->DrawText("Press [Space] to Start", 50, 100, 0xffffff00);
}

void MainMenu::OnDeactivate(System *system)
{
	system->GetGraphics()->DestroyXFont(titleFont_);
	titleFont_ = 0;
	system->GetGraphics()->DestroyXFont(optionsFont_);
	optionsFont_ = 0;
}
