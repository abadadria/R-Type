#ifndef _SCENELEVEL_INCLUDE
#define _SCENELEVEL_INCLUDE


#include "Scene.h"
#include "TileMap.h"
#include "Player.h"


// Scene contains all the entities of our game.
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

};


#endif // _SCENELEVEL_INCLUDE
