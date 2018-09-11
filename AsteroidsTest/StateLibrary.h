#ifndef STATELIBRARY_H_INCLUDED
#define STATELIBRARY_H_INCLUDED

#include <map>
#include <string>

class GameState;

class StateLibrary
{
public:
	StateLibrary();
	~StateLibrary();

	GameState *GetState(const std::string &stateId) const;

private:

	typedef std::map<std::string, GameState *> GameStateMap;

	void AddState(const std::string &stateId, GameState *state);

	GameStateMap states_;
};

#endif // STATELIBRARY_H_INCLUDED
