#ifndef GAMEOVER_H_INCLUDE
#define GAMEOVER_H_INCLUDE

#include "GameState.h"

class Font;

class GameOver : public GameState
{
public:
	GameOver();

	void OnActivate(System *system, StateArgumentMap &args);
	void OnUpdate(System *system);
	void OnRender(System *system);
	void OnDeactivate(System *system);

private:
	int delay_;
	Font *font_;
};

#endif // GAMEOVER_H_INCLUDE
