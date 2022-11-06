#ifndef _SCENELEVEL_INCLUDE
#define _SCENELEVEL_INCLUDE


#include <list>
#include "Scene.h"
#include "TileMap.h"
#include "Player.h"
#include "PassiveEntity.h"
#include "AutonomousEntity.h"
#include "Force.h"

#define NO_CHANGE 0
#define GOTO_MENU 1
#define RETRY 2
#define GAME_OVER 3


// SceneLevel contains all the entities of our game.
// It is responsible for updating and render them.


class SceneLevel : public Scene
{

public:
	SceneLevel();
	~SceneLevel();

	void load();
	void init() override;
	void update(int deltaTime) override;
	void render() override;

	int getChange();
	int getLives();
	void setLives(int newLives);

	int getScore() const;
	void setScore(int newScore);
	void increaseScore(int score);
	void decreaseScore(int score);

	void changeShowCollisionBlock();
	void changeCollisionsActivePlayer();

	void spawnForce();

	//First string is the getType(), second string is for extra information (e.g. direction of the bounce).
	vector<pair<string, string>> getCollisions(Entity* entity);

private:
	int getEnemySpawnColumn() const;

private:
	TileMap* map;
	Player* player;
	Force* force;
	std::list<AutonomousEntity*> enemies;
	std::list<PassiveEntity*> powerUps;

	bool playerDead;
	int change;

	int score;
	int lives;

	Text* text0;
	Text* text1;
	const glm::vec2 posScore = glm::vec2(140, 544 - 10);
	const glm::vec2 posLifes = glm::vec2(5, 544 - 10);
	const glm::vec2 posBeam = glm::vec2(320, 544 - 10);
	const int textSize = 15;
	glm::vec4 textColor;

	Sprite* spriteBeamStatus;
	Texture spritesheetBeamStatus;
	const glm::vec2 posBeamStatus = glm::vec2(390, 544 - 32);

	//la barra tiene 5 pixeles menos por las 4 caras respecto al Beamstatus
	Sprite* spriteBeamStatusBar;
	Texture spritesheetBeamStatusBar;
	const glm::vec2 posBeamStatusBar = glm::vec2(395, 544 - 27);

	Sprite* spriteAuxQuad;
	Texture spritesheetAuxQuad;

	Sprite* spriteBackHUDQuad;
	Texture spritesheetBackHUDQuad;
};


#endif // _SCENELEVEL_INCLUDE
