#ifndef BOOTSTATE_H_INCLUDED
#define BOOTSTATE_H_INCLUDED

#include "GameState.h"
#include <list>
#include <string>

class Font;
class AssetLoader;
class Graphics;

class BootState : public GameState
{
public:
	BootState();
	~BootState();

	void OnActivate(System *system, StateArgumentMap &args);
	void OnUpdate(System *system);
	void OnRender(System *system);
	void OnDeactivate(System *system);

private:

	enum State
	{
		STATE_BEGIN,
		STATE_LOADING_FONTS,
		STATE_LOADING_MODELS,
		STATE_LOADING_TEXTURES,
		STATE_LOADING_SOUNDS,
		STATE_END,
	};

	typedef std::list<std::string> StringList;

	void UpdateBegin(System *system);
	void UpdateLoadingFonts(System *system);
	void UpdateLoadingModels(System *system);
	void UpdateLoadingTextures(System *system);
	void UpdateLoadingSounds(System *system);
	void UpdateEnd(System *system);

	void CreateMeshFromAsset(const std::string &assetName,
		AssetLoader *loader,
		Graphics *graphics);

	State state_;
	StringList strings_;
	Font *font_;

	int fakeDelay_;
};

#endif // BOOTSTATE_H_INCLUDED
