#ifndef SYSTEM_H_INCLUDED
#define SYSTEM_H_INCLUDED

#include "GameState.h"
#include <Windows.h>
#include <string>

class MainWindow;
class Graphics;
class AssetLoader;
class StateLibrary;
class Keyboard;
class Game;

class System
{
public:
	System(HINSTANCE hInstance);
	~System();

	void Initialise();
	void Test();
	void Run();
	void Terminate();

	Graphics *GetGraphics() const;
	AssetLoader *GetAssetLoader() const;
	Keyboard *GetKeyboard() const;
	Game *GetGame() const;

	void SetNextState(const std::string &stateName);
	void SetNextState(const std::string &stateName,
		const GameState::StateArgumentMap &args);

private:
	System(const System &);
	void operator=(const System &);

	void ProcessMessageQueue();
	void SwapState();
	void Update();
	void Render();

	HINSTANCE moduleInstance_;
	MainWindow *mainWindow_;
	bool quit_;
	Graphics *graphics_;
	AssetLoader *assetLoader_;
	StateLibrary *stateLibrary_;
	Keyboard *keyboard_;

	GameState *currentState_;
	GameState *nextState_;
	GameState::StateArgumentMap nextStateArgs_;

	Game *game_;
};

#endif // SYSTEM_H_INCLUDED
