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
	Text* text1;
	const glm::vec2 posScore = glm::vec2(140, 544 - 10);
	const glm::vec2 posLives = glm::vec2(5, 544 - 10);
	const glm::vec2 posBeam = glm::vec2(320, 544 - 10);
	const int textSize = 15;
	const glm::vec4 textColor = glm::vec4(1.f, 1.f, 1.f, 1);

	Sprite* spriteBeamStatus;
	Texture spritesheetBeamStatus;
	const glm::vec2 posBeamStatus = glm::vec2(390, 544 - 32);

	//la barra tiene 5 pixeles menos por las 4 caras respecto al Beamstatus
	Sprite* spriteBeamStatusBar;
	Texture spritesheetBeamStatusBar;
	const glm::vec2 posBeamStatusBar = glm::vec2(395, 544 - 27);
};


#endif // _SCENELEVEL_INCLUDE
