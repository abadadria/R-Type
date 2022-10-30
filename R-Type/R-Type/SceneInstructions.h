#ifndef _SCENEINSTRUCTIONS_INCLUDE
#define _SCENEINSTRUCTIONS_INCLUDE


#include "Scene.h"


class SceneInstructions : public Scene
{
public:
	SceneInstructions();
	~SceneInstructions();

	void init() override;
	void update(int deltaTime) override;
	void render() override;

private:

};

#endif // _SCENEINSTRUCTIONS_ INCLUDE