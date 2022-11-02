#ifndef _SCENECREDITS_INCLUDE
#define _SCENECREDITS_INCLUDE


#include "Scene.h"
#include "Text.h"

class SceneCredits : public Scene
{
public:
	SceneCredits();
	~SceneCredits();

	void init() override;
	void update(int deltaTime) override;
	void render() override;

private:
	Text* text0;
	Text* text1;
	Text* text2;

	const glm::vec2 posBack = glm::vec2(10, 25);
	const int textBackSize = 20;
	const glm::vec4 textBackColor = glm::vec4(0.8, 0.6, 0.8, 1);

	const glm::vec2 posCred = glm::vec2(230, 80);
	const int textCredSize = 35;
	const glm::vec4 textColor = glm::vec4(0, 0.6, 0.6, 1);

	const glm::vec2 posElem = glm::vec2(215, 150);
	const int textElemSize = 20;
	const glm::vec4 textElemColor = glm::vec4(1, 1, 1, 1);


};

#endif // _SCENECREDITS_ INCLUDE