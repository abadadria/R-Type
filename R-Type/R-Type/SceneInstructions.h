#ifndef _SCENEINSTRUCTIONS_INCLUDE
#define _SCENEINSTRUCTIONS_INCLUDE


#include "Scene.h"
#include "Text.h"


class SceneInstructions : public Scene
{
public:
	SceneInstructions();
	~SceneInstructions();

	void init() override;
	void update(int deltaTime) override;
	void render() override;

private:
	Text* text0;
	Text* text1;

	const glm::vec2 posBack = glm::vec2(10, 25);
	const int textBackSize = 20;
	const glm::vec4 textBackColor = glm::vec4(0.8, 0.6, 0.8, 1);

	const glm::vec2 posInst = glm::vec2(30, 80);
	const int textInstSize = 35;
	const glm::vec4 textColor = glm::vec4(0, 0.6, 0.6, 1);

	const glm::vec2 posElem = glm::vec2(28, 130);
	const int textElemSize = 15;
	const glm::vec4 textElemColor = glm::vec4(0, 0.4, 0.4, 1);
};

#endif // _SCENEINSTRUCTIONS_ INCLUDE