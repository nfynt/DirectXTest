#include "StateLibrary.h"
#include "BootState.h"
#include "GameState.h"
#include "MainMenu.h"
#include "LevelStart.h"
#include "PlayingState.h"
#include "GameOver.h"

StateLibrary::StateLibrary()
{
	AddState("BootState", new BootState());
	AddState("MainMenu", new MainMenu());
	AddState("LevelStart", new LevelStart());
	AddState("PlayingState", new PlayingState());
	AddState("GameOver", new GameOver());
}

StateLibrary::~StateLibrary()
{
	for (GameStateMap::iterator stateIt = states_.begin(), end = states_.end();
		stateIt != end;
		++stateIt)
	{
		delete stateIt->second;
	}
}

GameState *StateLibrary::GetState(const std::string &stateId) const
{
	GameStateMap::const_iterator stateIt = states_.find(stateId);
	if (stateIt != states_.end())
	{
		return stateIt->second;
	}
	return 0;
}

void StateLibrary::AddState(const std::string &stateId, GameState *state)
{
	states_.insert(std::make_pair(stateId, state));
}
