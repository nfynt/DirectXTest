#ifndef GAMESTATE_H_INCLUDED
#define GAMESTATE_H_INCLUDED

#include <map>
#include <string>

class System;

class GameState
{
public:

	union StateArgument
	{
		int asInt;
		float asFloat;
		void *asPointer;
	};

	typedef std::map<std::string, StateArgument> StateArgumentMap;

	GameState();
	virtual ~GameState();

	virtual void OnActivate(System *system, StateArgumentMap &args) = 0;
	virtual void OnUpdate(System *system) = 0;
	virtual void OnRender(System *system) = 0;
	virtual void OnDeactivate(System *system) = 0;

private:
	GameState(const GameState &);
	void operator=(const GameState &);

};

#endif // SCREEN_H_INCLUDED
