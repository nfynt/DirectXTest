#include "Game.h"
#include "System.h"
#include "OrthoCamera.h"
#include "Background.h"
#include "Ship.h"
#include "Asteroid.h"
#include "Explosion.h"
#include "Keyboard.h"
#include "Random.h"
#include "Maths.h"
#include "Bullet.h"
#include "Collision.h"
#include <algorithm>
#include "stdlib.h"
#include "Font.h"
#include "Graphics.h"
#include <thread>
#include <string.h>
#include "Enemy.h"


Game::Game() :
	camera_(0),
	background_(0),
	player_(0),
	collision_(0)
{
	//titleFont_ = system->GetGraphics()->CreateXFont("Arial", 48);
	scoreTxt_ = 0;
	popScoreTxt_ = 0;
	
	scorePopDur_ = 0;
	//popTxtPos_.x = popTxtPos_.y = 0;
	scorePopStr_ = "";

	camera_ = new OrthoCamera();
	camera_->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	camera_->SetFrustum(800.0f, 600.0f, -100.0f, 100.0f);
	background_ = new Background(800.0f, 600.0f);
	collision_ = new Collision();
	//bullet_ = new Bullet(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	currScore_ = 0;
}

Game::~Game()
{
	delete camera_;
	delete background_;
	delete player_;
	//DeleteBullet();
	DeleteAllBullets(); 
	DeleteAllAsteroids();
	DeleteAllExplosions();
	DeleteAllEnemies();
	delete collision_;
}

void Game::Update(System *system)
{
	UpdatePlayer(system);
	UpdateAsteroids(system);
	UpdateEnemies(system);
	UpdateBullet(system);
	UpdateCollisions();

	if (scoreTxt_ == 0)
	{
		scoreTxt_ = system->GetGraphics()->CreateXFont("Arial", 32);
		popScoreTxt_= system->GetGraphics()->CreateXFont("Arial", 26);
	}
}

void Game::RenderBackgroundOnly(Graphics *graphics)
{
	camera_->SetAsView(graphics);
	background_->Render(graphics);
}

void Game::RenderEverything(Graphics *graphics)
{
	camera_->SetAsView(graphics);

	background_->Render(graphics);

	if (player_)
	{
		player_->Render(graphics);
	}

	for (AsteroidList::const_iterator asteroidIt = asteroids_.begin(),
		end = asteroids_.end();
		asteroidIt != end;
		++asteroidIt)
	{
		(*asteroidIt)->Render(graphics);
	}
	
	for (BulletList::const_iterator bit = bullets_.begin(); bit != bullets_.end(); ++bit)
	{
		if (*bit)
		{	
			(*bit)->Render(graphics);
		}
	}

	for (EnemyList::const_iterator eit = enemies_.begin(); eit != enemies_.end(); ++eit)
	{
		if (*eit)
		{
			(*eit)->Render(graphics);
		}
	}

	for (ExplosionList::const_iterator explosionIt = explosions_.begin(),
		end = explosions_.end();
		explosionIt != end;
		++explosionIt)
	{
		(*explosionIt)->Render(graphics);
	}
	
	if (scoreTxt_ != 0)
		scoreTxt_->DrawText("SCORE: " + std::to_string(currScore_), 50, 50, 0xffffff00);
	if(--scorePopDur_>0)
		popScoreTxt_->DrawText("             "+scorePopStr_, 80, 80, 0xffff0000);
}

void Game::InitialiseLevel(int numAsteroids)
{
	currLevel_ = numAsteroids;

	DeleteAllAsteroids();
	DeleteAllExplosions();
	DeleteAllBullets();
	DeleteAllEnemies();

	SpawnPlayer();
	SpawnAsteroids(numAsteroids);

	if (currLevel_==1 && currScore_ > 0)
		currScore_ = 0;
	if (scorePopDur_ > 0)
		scorePopDur_ = 0;

	if (currLevel_ > 2)
	{
		float halfWidth = 800.0f * 0.5f;
		float halfHeight = 600.0f * 0.5f;
		int side = currLevel_ % 4;
		float x, y;
		x = y = 0.0f;
		D3DXVECTOR3 position, velocity;
		position = velocity = D3DXVECTOR3(0, 0, 0);

		switch (side)
		{
		case 0:
			x = Random::GetFloat(-halfWidth, halfWidth);
			y = 0.0f;
			position = D3DXVECTOR3(x, y, 0.0f);

			break;

		case 1:
			x = 800.0f;
			y = Random::GetFloat(-halfHeight, halfHeight);
			position = D3DXVECTOR3(x, y, 0.0f);

			break;

		case 2:
			x = Random::GetFloat(-halfWidth, halfWidth);
			y = 600.0f;
			position = D3DXVECTOR3(x, y, 0.0f);

			break;

		case 3:
			x = 0.0f;
			y = Random::GetFloat(-halfHeight, halfHeight);
			position = D3DXVECTOR3(x, y, 0.0f);

			break;
		}
		const D3DXVECTOR3 pos = D3DXVECTOR3(x,y,0), plyr = D3DXVECTOR3(player_->GetPosition());
		//const D3DXVECTOR3 up = D3DXVECTOR3(0, 1, 0);
		//D3DXVECTOR3 *d;
		//D3DXVECTOR3 *right;
		D3DXVec3Subtract(&velocity, &pos, &plyr);
		//D3DXVec3Cross(right, &up, d);
		//D3DXVec3Normalize(right, right);
		D3DXVec3Normalize(&velocity, &velocity);
		//velocity = D3DXVec3Subtract(*velocity, *playerPos2, *playerPos);
		SpawnEnemy(position, -velocity);
	}
}

bool Game::IsLevelComplete() const
{
	return (asteroids_.empty() && explosions_.empty() && enemies_.empty());
}

bool Game::IsGameOver() const
{
	return (player_ == 0 && explosions_.empty());
}

void Game::DoCollision(GameEntity *a, GameEntity *b)
{
	Ship *player = static_cast<Ship *>(a == player_ ? a : (b == player_ ? b : 0));
	Bullet *bullet = static_cast<Bullet *>(IsBullet(a)? a : (IsBullet(b)? b : 0));
	Asteroid *asteroid = static_cast<Asteroid *>(IsAsteroid(a) ? a : (IsAsteroid(b) ? b : 0));
	Enemy *enemy = static_cast<Enemy *>(IsEnemy(a) ? a : (IsEnemy(b) ? b : 0));

	if (player && asteroid)
	{
		AsteroidHit(asteroid);
		DeletePlayer();
	}

	if (bullet && asteroid)
	{
		scorePopDur_ = 100;
		//popTxtPos_.x = std::abs(asteroid->GetPosition().x);
		//popTxtPos_ = asteroid->GetPosition();
		AsteroidHit(asteroid);
		//DeleteBullet();
		DeleteBullet(bullet);
	}

	if (bullet && enemy)
	{
		scorePopDur_ = 100;
		currScore_ += 100;
		scorePopStr_ = "+100";
		DeleteBullet(bullet);
		DeleteEnemy(enemy);
	}

	if (enemy && player)
	{
		//DeleteAllEnemies();
		DeletePlayer();
	}
}

void Game::SpawnPlayer()
{
	DeletePlayer();
	player_ = new Ship();
	player_->EnableCollisions(collision_, 10.0f);
}

void Game::DeletePlayer()
{
	delete player_;
	player_ = 0;
}

void Game::UpdatePlayer(System *system)
{
	if (player_ == 0)
		return;

	Keyboard *keyboard = system->GetKeyboard();

	float acceleration = 0.0f;
	if (keyboard->IsKeyHeld(VK_UP) || keyboard->IsKeyHeld('W'))
	{
		acceleration = 1.0f;
	}
	else if (keyboard->IsKeyHeld(VK_DOWN) || keyboard->IsKeyHeld('S'))
	{
		acceleration = -1.0f;
	}

	float rotation = 0.0f;
	if (keyboard->IsKeyHeld(VK_RIGHT) || keyboard->IsKeyHeld('D'))
	{
		rotation = -1.0f;
	}
	else if (keyboard->IsKeyHeld(VK_LEFT) || keyboard->IsKeyHeld('A'))
	{
		rotation = 1.0f;
	}

	player_->SetControlInput(acceleration, rotation);
	player_->Update(system);
	WrapEntity(player_);

	if (keyboard->IsKeyPressed(VK_SPACE))
	{
		D3DXVECTOR3 playerForward = player_->GetForwardVector();
		D3DXVECTOR3 bulletPosition = player_->GetPosition() + playerForward * 10.0f;
		SpawnBullet(bulletPosition, playerForward);
	}else if (keyboard->IsKeyPressed(VK_CONTROL))
	{
		//std::thread bFire(BurstSpawnBullets,3);
		BurstSpawnBullets(3);
	}
}

void Game::SpawnEnemy(const D3DXVECTOR3 &position,
	const D3DXVECTOR3 &velocity)
{
	enemies_.push_back(new Enemy(position,velocity,player_));
	enemies_.back()->EnableCollisions(collision_, 15.0f);
}

void Game::UpdateEnemies(System *system)
{
	for (EnemyList::const_iterator enit = enemies_.begin(),
		end = enemies_.end();
		enemies_.size() > 0 && enit != end;
		++enit)
	{
		(*enit)->Update(system);
		WrapEntity(*enit);

	}
}

void Game::DeleteEnemy(Enemy *enemyRef)
{
	enemies_.remove(enemyRef);
	delete(enemyRef);
}

void Game::DeleteAllEnemies()
{
	for (EnemyList::iterator eit = enemies_.begin(), end = enemies_.end(); eit != end; eit++)
		delete(*eit);

	enemies_.clear();
}

void Game::BurstSpawnBullets(int cnt=-1)
{
	if (cnt == -1)
	{
		burstCount_--;
		if (burstCount_%burstDelay_ == 0) {
			D3DXVECTOR3 playerForward = player_->GetForwardVector();
			D3DXVECTOR3 bulletPosition = player_->GetPosition() + playerForward * 10.0f;
			SpawnBullet(bulletPosition, playerForward);
		}
		if (burstCount_ <= 0)
			spawnBurst_ = false;
	}
	else {
		spawnBurst_ = true;
		burstCount_ = cnt*burstDelay_;
	}
		
	
}

void Game::UpdateAsteroids(System *system)
{
	for (AsteroidList::const_iterator asteroidIt = asteroids_.begin(),
		end = asteroids_.end();
		asteroidIt != end;
	++asteroidIt)
	{
		(*asteroidIt)->Update(system);
		WrapEntity(*asteroidIt);
	}
}

void Game::UpdateBullet(System *system)
{
	for (BulletList::const_iterator bit = bullets_.begin(),
		end = bullets_.end();
		bullets_.size()>0 && bit != end;
		++bit)
	{
		if ((*bit)->lifeTime > 0) {
			(*bit)->Update(system); //access violation crash
			WrapEntity(*bit);
		}
		else {
			DeleteBullet(*bit);
			break;
		}
	}

	if (spawnBurst_)
	{
		BurstSpawnBullets();
	}

	//if (bullet_!=NULL)
	//{
	//	if (bullet_->lifeTime > 0) {
	//		bullet_->Update(system); //access violation crash
	//		WrapEntity(bullet_);
	//	}
	//	else {
	//		DeleteBullet(bullet_);
	//	}
	//}
}

void Game::WrapEntity(GameEntity *entity) const
{
	D3DXVECTOR3 entityPosition = entity->GetPosition();
	entityPosition.x = Maths::WrapModulo(entityPosition.x, -400.0f, 400.0f);
	entityPosition.y = Maths::WrapModulo(entityPosition.y, -300.0f, 300.0f);
	entity->SetPosition(entityPosition);
}

void Game::DeleteAllAsteroids()
{
	for (AsteroidList::const_iterator asteroidIt = asteroids_.begin(),
		end = asteroids_.end();
		asteroidIt != end;
		++asteroidIt)
	{
		delete (*asteroidIt);
	}

	asteroids_.clear();
}

void Game::DeleteAllExplosions()
{
	for (ExplosionList::const_iterator explosionIt = explosions_.begin(),
		end = explosions_.end();
		explosionIt != end;
	++explosionIt)
	{
		delete (*explosionIt);
	}

	explosions_.clear();
}

void Game::DeleteAllBullets()
{
	for (BulletList::const_iterator bit = bullets_.begin(),
		end = bullets_.end();
		bit != end;
		++bit)
	{
		delete(*bit);
	}
	bullets_.clear();
}

void Game::SpawnBullet(const D3DXVECTOR3 &position,
	const D3DXVECTOR3 &direction)
{
	/*DeleteBullet();
	bullet_ = new Bullet(position, direction);
	bullet_->EnableCollisions(collision_, 3.0f);*/
	bullets_.push_back(new Bullet(position, direction));
	bullets_.back()->EnableCollisions(collision_, 3.0f);
}

void Game::DeleteBullet(Bullet *bulletRef)
{
	bullets_.remove(bulletRef);
	delete bulletRef;

	//delete bulletRef;
	//bullet_ = 0;
}

void Game::SpawnAsteroids(int numAsteroids)
{
	float halfWidth = 800.0f * 0.5f;
	float halfHeight = 600.0f * 0.5f;
	for (int i = 0; i < numAsteroids; i++)
	{
		float x = Random::GetFloat(-halfWidth, halfWidth);
		float y = Random::GetFloat(-halfHeight, halfHeight);
		D3DXVECTOR3 position = D3DXVECTOR3(x, y, 0.0f);
		SpawnAsteroidAt(position, 3);
	}
}

void Game::SpawnAsteroidAt(const D3DXVECTOR3 &position, int size)
{
	const float MAX_ASTEROID_SPEED = 1.0f;

	float angle = Random::GetFloat(Maths::TWO_PI);
	D3DXMATRIX randomRotation;
	D3DXMatrixRotationZ(&randomRotation, angle);
	D3DXVECTOR3 velocity = D3DXVECTOR3(0.0f, Random::GetFloat(MAX_ASTEROID_SPEED), 0.0f);
	D3DXVec3TransformNormal(&velocity, &velocity, &randomRotation);

	Asteroid *asteroid = new Asteroid(position, velocity, size);
	asteroid->EnableCollisions(collision_, size * 5.0f);
	asteroids_.push_back(asteroid);
}

bool Game::IsAsteroid(GameEntity *entity) const
{
	return (std::find(asteroids_.begin(),
		asteroids_.end(), entity) != asteroids_.end()); 
}

bool Game::IsBullet(GameEntity *entity) const
{
	return (std::find(bullets_.begin(),
		bullets_.end(), entity) != bullets_.end());
}

bool Game::IsEnemy(GameEntity *entity) const
{
	return (std::find(enemies_.begin(),
		enemies_.end(), entity) != enemies_.end());
}

void Game::AsteroidHit(Asteroid *asteroid)
{
	int oldSize = asteroid->GetSize();
	
	if (oldSize == 3)
	{
		currScore_ += 10;
		scorePopStr_ = "+10";
	}
	else if (oldSize == 2)
	{
		currScore_ += 20;
		scorePopStr_ = "+20";
	}
	else if (oldSize == 1)
	{
		currScore_ += 50;
		scorePopStr_ = "+50";
	}

	if (oldSize > 1)
	{
		int smallerSize = oldSize -1;
		D3DXVECTOR3 position = asteroid->GetPosition();
		SpawnAsteroidAt(position, smallerSize);
		SpawnAsteroidAt(position, smallerSize);
	}
	DeleteAsteroid(asteroid);
}

void Game::DeleteAsteroid(Asteroid *asteroid)
{
	asteroids_.remove(asteroid);
	delete asteroid;
}

void Game::UpdateCollisions()
{
	collision_->DoCollisions(this);
}
