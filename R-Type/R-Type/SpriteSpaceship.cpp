#include "SpriteSpaceship.h"

enum PlayerAnims
{
	STAND, MOVE_UP, MOVE_DOWN, GO_BACK
};

SpriteSpaceship::SpriteSpaceship(const glm::vec2& quadSize, const glm::vec2& sizeInSpritesheet, Texture* spritesheet, ShaderProgram* program):
	Sprite(quadSize, sizeInSpritesheet, spritesheet, program) {};

SpriteSpaceship* SpriteSpaceship::createSpriteSpaceship(const glm::vec2& quadSize, const glm::vec2& sizeInSpritesheet, Texture* spritesheet, ShaderProgram* program) {
	SpriteSpaceship* quad = new SpriteSpaceship(quadSize, sizeInSpritesheet, spritesheet, program);

	return quad;
}

void SpriteSpaceship::update(int deltaTime) {
	if (currentAnimation == STAND) return;

	if (currentAnimation == GO_BACK) {
		if (currentKeyframe == 2) {
			changeAnimation(STAND);
		}
		else if (currentKeyframe > 2) {
			continueAnimation(deltaTime, false, false);
		}
		else /*if (currentKeyframe < 2)*/ {
			continueAnimation(deltaTime, true, false);
		}
	}
	else if (currentAnimation == MOVE_UP) {
		continueAnimation(deltaTime, true, false);
	}
	else if (currentAnimation == MOVE_DOWN) {
		continueAnimation(deltaTime, false, false);
	}
}

void SpriteSpaceship::changeAnimation(int animId) {
	if (animId < int(animations.size()))
	{
		int prevAnimation = currentAnimation;
		currentAnimation = animId;
		timeAnimation = 0.f;
		if (currentAnimation == STAND) {
			currentKeyframe = 0;
			texCoordDispl = animations[animId].keyframeDispl[0];
		}
		else if (prevAnimation == STAND && (currentAnimation == MOVE_UP || currentAnimation == MOVE_DOWN)) {
			currentKeyframe = 2;
			texCoordDispl = animations[animId].keyframeDispl[2];
		}
	}
}