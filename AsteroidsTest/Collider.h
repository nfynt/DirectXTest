#ifndef COLLIDER_H_INCLUDED
#define COLLIDER_H_INCLUDED

#include <d3dx9math.h>

class GameEntity;

class Collider
{
	friend class Collision;
private:
	D3DXVECTOR3 position;
	float radius;
	GameEntity *entity;
	bool enabled;
};

#endif // COLLIDER_H_INCLUDED
