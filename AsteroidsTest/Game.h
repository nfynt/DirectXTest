#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <d3dx9math.h>
#include "GameState.h"
#include <list>
#include <string.h>

class OrthoCamera;
class Background;
class Ship;
class Bullet;
class Asteroid;
class Explosion;
class Collision;
class System;
class Graphics;
class GameEntity;
class Font;
class Enemy;

class Game
{
public:
	Game();
	~Game();

	void Update(System *system);
	void RenderBackgroundOnly(Graphics *graphics);
	void RenderEverything(Graphics *graphics);

	void InitialiseLevel(int numAsteroids);
	bool IsLevelComplete() const;
	bool IsGameOver() const;

	void DoCollision(GameEntity *a, GameEntity *b);
	void BurstSpawnBullets(int cnt);

private:
	Game(const Game &);
	void operator=(const Game &);

	typedef std::list<Asteroid *> AsteroidList;
	typedef std::list<Explosion *> ExplosionList;
	typedef std::list<Bullet *> BulletList;
	typedef std::list<Enemy *> EnemyList;

	void SpawnPlayer();
	void DeletePlayer();

	void UpdatePlayer(System *system);
	void UpdateAsteroids(System *system);
	void UpdateBullet(System *system);
	void UpdateEnemies(System *system);
	void WrapEntity(GameEntity *entity) const;

	void DeleteAllAsteroids();
	void DeleteAllExplosions();

	void SpawnBullet(const D3DXVECTOR3 &position,
		const D3DXVECTOR3 &direction);
	//void DeleteBullet();
	void DeleteBullet(Bullet *bulletRef);
	void DeleteAllBullets();

	void SpawnAsteroids(int numAsteroids);
	void SpawnAsteroidAt(const D3DXVECTOR3 &position, int size);
	bool IsAsteroid(GameEntity *entity) const;
	bool IsBullet(GameEntity *entity) const;
	bool IsEnemy(GameEntity *entity) const;
	void AsteroidHit(Asteroid *asteroid);
	void DeleteAsteroid(Asteroid *asteroid);

	void SpawnEnemy(const D3DXVECTOR3 &position,
		const D3DXVECTOR3 &direction);
	void DeleteEnemy(Enemy *enemy);
	void DeleteAllEnemies();

	void UpdateCollisions();

	OrthoCamera *camera_;

	Background *background_;
	Ship *player_;
	//std::list<Bullet*> bullet_;
	AsteroidList asteroids_;
	ExplosionList explosions_;
	BulletList bullets_;
	EnemyList enemies_;

	Collision *collision_;

	//Show text on screen
	Font *scoreTxt_;
	Font *popScoreTxt_;
	int scorePopDur_;
	//D3DXVECTOR3 popTxtPos_;
	std::string scorePopStr_;

	//Burst bullet spawn
	bool spawnBurst_;
	int burstCount_;
	int burstDelay_=3;

	//Game score
	int currScore_;
	int currLevel_;
};

#endif // GAME_H_INCLUDED
