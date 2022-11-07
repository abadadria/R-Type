#ifndef _SCENEMENU_INCLUDE
#define _SCENEMENU_INCLUDE


#include "Scene.h"
#include "Sprite.h"
#include "Texture.h"

#define PLAY 0
#define INST 1
#define CRED 2
#define EXIT 3


class SceneMenu : public Scene
{
public:
	SceneMenu();
	~SceneMenu();

	void init() override;
	void update(int deltaTime) override;
	void render() override;
	int getItemSelected();
	void setItemSelected(int newSelected);

private:

	Sprite* spriteLogo;
	Texture spritesheetLogo;
	const glm::vec2 sizeLogo = glm::vec2(450, 112);
	const glm::vec2 posLogo = glm::vec2(320 - 450 /2, 50);
	
	Text* text;
	
	int textSelected;
	int changeSelected;
	const int textSize = 40;
	const glm::vec2 posPlay = glm::vec2(260, 256);
	const glm::vec2 posInst = glm::vec2(164, 256 + 60);
	const glm::vec2 posCred = glm::vec2(220, 256 + 120);
	const glm::vec2 posExit = glm::vec2(260, 256 + 180);
	const glm::vec4 selectedTextColor = glm::vec4(0.5, 0.6, 0.6, 1);
	const glm::vec4 textColor = glm::vec4(0, 0.6, 0.6, 1);
	
};

#endif // _SCENEMENU_INCLUDE

