#ifndef _SCENELEVEL_INCLUDE
#define _SCENELEVEL_INCLUDE


#include "Scene.h"
#include "TileMap.h"
#include "Player.h"
#include "PassiveEntity.h"


// SceneLevel contains all the entities of our game.
// It is responsible for updating and render them.


class SceneLevel : public Scene
{

public:
	SceneLevel();
	~SceneLevel();

	void init() override;
	void update(int deltaTime) override;
	void render() override;

private:
	TileMap* map;
	Player* player;

	int score; // TODO implementar cuando haya colisiones entre entityes
	int lives;

	Text* text0;
	const glm::vec2 posScore = glm::vec2(544 - 30, 5);
	const glm::vec2 posLives = glm::vec2(544 - 30, 50);
	const int textSize = 30;
	const glm::vec4 textColor = glm::vec4(0.8, 0.6, 0.8, 1);

	Sprite* spriteBeamStatus;
	Texture spritesheetBeamStatus;

	Sprite* spriteBeamStatusFiller;
	Texture spritesheetBeamStatusFiller;
};


#endif // _SCENELEVEL_INCLUDE
