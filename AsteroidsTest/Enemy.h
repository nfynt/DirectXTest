#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include "GameEntity.h"

class Ship;

class Enemy : public GameEntity
{
public:
	Enemy(const D3DXVECTOR3 &position,
		const D3DXVECTOR3 &velocity,
		Ship *target);

	void Update(System *system);
	void Render(Graphics *graphics) const;

	D3DXVECTOR3 GetVelocity() const;
	int GetSize() const;

private:

	D3DXVECTOR3 velocity_;
	D3DXVECTOR3 axis_;
	float angle_;
	int size_;
	Ship *targetShip;

	//Attack
	int fireDelay;


};

#endif // SHIP_H_INCLUDED
