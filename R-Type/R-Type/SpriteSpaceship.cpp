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
				timeAnimation += deltaTime;
				while (timeAnimation > animations[currentAnimation].millisecsPerKeyframe)
				{
					timeAnimation -= animations[currentAnimation].millisecsPerKeyframe;
					currentKeyframe = (currentKeyframe - 1) % animations[currentAnimation].keyframeDispl.size();
				}
				texCoordDispl = animations[currentAnimation].keyframeDispl[currentKeyframe];
			}
			else /*if (currentKeyframe < 2)*/ {
				timeAnimation += deltaTime;
				while (timeAnimation > animations[currentAnimation].millisecsPerKeyframe)
				{
					timeAnimation -= animations[currentAnimation].millisecsPerKeyframe;
					currentKeyframe = (currentKeyframe + 1) % animations[currentAnimation].keyframeDispl.size();
				}
				texCoordDispl = animations[currentAnimation].keyframeDispl[currentKeyframe];
			}
		}
		else /*currentAnimation in {MOVE_UP, MOVE_DOWN}*/ {
			if (currentAnimation == MOVE_UP && currentKeyframe == animations[currentAnimation].keyframeDispl.size() - 1) {
				changeAnimation(STAND_UP);
			}
			if (currentAnimation == MOVE_DOWN && currentKeyframe == animations[currentAnimation].keyframeDispl.size() - 1) {
				changeAnimation(STAND_DOWN);
			}
			else {
				timeAnimation += deltaTime;
				while (timeAnimation > animations[currentAnimation].millisecsPerKeyframe)
				{
					timeAnimation -= animations[currentAnimation].millisecsPerKeyframe;
					currentKeyframe = (currentKeyframe + 1) % animations[currentAnimation].keyframeDispl.size();
				}
				texCoordDispl = animations[currentAnimation].keyframeDispl[currentKeyframe];
			}

		}
	}
}

void SpriteSpaceship::changeAnimation(int animId) {
	if (animId < int(animations.size()))
	{
		// TODO: Definir las transiciones entre animaciones. De STAND* a otras se resetea el keyframe al 0.
		currentAnimation = animId;
		timeAnimation = 0.f;
		if (currentAnimation == STAND || currentAnimation == STAND_DOWN || currentAnimation == STAND_UP) {
			currentKeyframe = 0;
			texCoordDispl = animations[animId].keyframeDispl[0];
		}
	}
}