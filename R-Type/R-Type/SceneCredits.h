#ifndef _SCENECREDITS_INCLUDE
#define _SCENECREDITS_INCLUDE


#include "Scene.h"


class SceneCredits : public Scene
{
public:
	SceneCredits();
	~SceneCredits();

	void init() override;
	void update(int deltaTime) override;
	void render() override;

private:

};

#endif // _SCENECREDITS_ INCLUDE