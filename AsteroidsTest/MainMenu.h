#ifndef MAINMENU_H_INCLUDED
#define MAINMENU_H_INCLUDED

#include "GameState.h"

class Font;

class MainMenu : public GameState
{
public:
	MainMenu();
	~MainMenu();

	void OnActivate(System *system, StateArgumentMap &args);
	void OnUpdate(System *system);
	void OnRender(System *system);
	void OnDeactivate(System *system);

private:

	Font *titleFont_;
	Font *optionsFont_;

};

#endif // MAINMENU_H_INCLUDED
