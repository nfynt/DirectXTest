#ifndef BACKGROUND_H_INCLUDED
#define BACKGROUND_H_INCLUDED

#include "GameEntity.h"

class Background : public GameEntity
{
public:
	Background(float width, float height);

	void Update(System *system);
	void Render(Graphics *graphics) const;

private:

	struct StarVertex
	{
		float x, y, z;
		D3DCOLOR diffuse;
	};

	enum { NUM_STARS = 256 };

	StarVertex stars_[NUM_STARS];

};

#endif // BACKGROUND_H_INCLUDED
