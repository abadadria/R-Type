#include "SpriteSpaceship.h"

enum PlayerAnims
{
	STAND, STAND_UP, STAND_DOWN, MOVE_UP, MOVE_DOWN, GO_BACK
};

SpriteSpaceship::SpriteSpaceship(const glm::vec2& quadSize, const glm::vec2& sizeInSpritesheet, Texture* spritesheet, ShaderProgram* program) : Sprite(quadSize, sizeInSpritesheet, spritesheet, program) {};

SpriteSpaceship* SpriteSpaceship::createSpriteSpaceship(const glm::vec2& quadSize, const glm::vec2& sizeInSpritesheet, Texture* spritesheet, ShaderProgram* program) {
	SpriteSpaceship* quad = new SpriteSpaceship(quadSize, sizeInSpritesheet, spritesheet, program);

	return quad;
}

void SpriteSpaceship::update(int deltaTime) {
	if (currentAnimation != STAND && currentAnimation != STAND_DOWN && currentAnimation != STAND_UP)
	{
		if (currentAnimation == GO_BACK) {
			if (currentKeyframe == 2) {
				changeAnimation(STAND);
			}
			else if (currentKeyframe > 2) {
				continueAnimation(deltaTime, false);
			}
			else /*if (currentKeyframe < 2)*/ {
				continueAnimation(deltaTime, true);
			}
		}
		else if (currentAnimation == MOVE_UP) {
			if (currentKeyframe == animations[currentAnimation].keyframeDispl.size() - 1)
				changeAnimation(STAND_UP);
			else
				continueAnimation(deltaTime, true);
		}
		else if (currentAnimation == MOVE_DOWN) {
			if (currentKeyframe == animations[currentAnimation].keyframeDispl.size() - 1)
				changeAnimation(STAND_DOWN);
			else
				continueAnimation(deltaTime, false);
		}
	}
}

void SpriteSpaceship::changeAnimation(int animId) {
	if (animId < int(animations.size()))
	{
		int prevAnimation = currentAnimation;
		currentAnimation = animId;
		timeAnimation = 0.f;
		if (currentAnimation == STAND || currentAnimation == STAND_DOWN || currentAnimation == STAND_UP) {
			currentKeyframe = 0;
			texCoordDispl = animations[animId].keyframeDispl[0];
		}
	}
}