#ifndef _SPRITE_SPACESHIP_INCLUDE
#define _SPRITE_SPACESHIP_INCLUDE


#include "Sprite.h"

class SpriteSpaceship : public Sprite
{
	private:
		SpriteSpaceship(const glm::vec2& quadSize, const glm::vec2& sizeInSpritesheet, Texture* spritesheet, ShaderProgram* program);

	public:
		static SpriteSpaceship* createSpriteSpaceship(const glm::vec2& quadSize, const glm::vec2& sizeInSpritesheet, Texture* spritesheet, ShaderProgram* program);

		void update(int deltaTime) override;

		void changeAnimation(int animId) override;
};


#endif