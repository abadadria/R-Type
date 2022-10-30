#ifndef _SCENEMENU_INCLUDE
#define _SCENEMENU_INCLUDE


#include "Scene.h"
#include "Sprite.h"
#include "Texture.h"
#include "Text.h"


class SceneMenu : public Scene
{
public:
	SceneMenu();
	~SceneMenu();

	void init() override;
	void update(int deltaTime) override;
	void render() override;

private:

	Sprite* spriteLogo;
	Texture spritesheetLogo;
	const glm::vec2 sizeLogo = glm::vec2(346, 86);
	const glm::vec2 posLogo = glm::vec2(0, 0);
	Text* text;
	
};

#endif // _SCENEMENU_INCLUDE

