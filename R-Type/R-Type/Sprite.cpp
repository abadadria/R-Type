#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Sprite.h"

enum PlayerAnims
{
	STAND, STAND_UP, STAND_DOWN, MOVE_UP, MOVE_DOWN, GO_BACK
};

Sprite *Sprite::createSprite(const glm::vec2 &quadSize, const glm::vec2 &sizeInSpritesheet, Texture *spritesheet, ShaderProgram *program)
{
	Sprite *quad = new Sprite(quadSize, sizeInSpritesheet, spritesheet, program);

	return quad;
}


Sprite::Sprite(const glm::vec2 &quadSize, const glm::vec2 &sizeInSpritesheet, Texture *spritesheet, ShaderProgram *program)
{
	float vertices[24] = {0.f, 0.f, 0.f, 0.f, 
												quadSize.x, 0.f, sizeInSpritesheet.x, 0.f, 
												quadSize.x, quadSize.y, sizeInSpritesheet.x, sizeInSpritesheet.y, 
												0.f, 0.f, 0.f, 0.f, 
												quadSize.x, quadSize.y, sizeInSpritesheet.x, sizeInSpritesheet.y, 
												0.f, quadSize.y, 0.f, sizeInSpritesheet.y};

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), vertices, GL_STATIC_DRAW);
	posLocation = program->bindVertexAttribute("position", 2, 4*sizeof(float), 0);
	texCoordLocation = program->bindVertexAttribute("texCoord", 2, 4*sizeof(float), (void *)(2*sizeof(float)));
	texture = spritesheet;
	shaderProgram = program;
	currentAnimation = -1;
	position = glm::vec2(0.f);
}

void Sprite::update(int deltaTime)
{
	if(currentAnimation != STAND && currentAnimation != STAND_DOWN && currentAnimation != STAND_UP)
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
			if (currentAnimation == MOVE_UP && currentKeyframe == animations[currentAnimation].keyframeDispl.size() -1) {
				changeAnimation(STAND_UP);
			}
			if (currentAnimation == MOVE_DOWN && currentKeyframe == animations[currentAnimation].keyframeDispl.size() -1) {
				changeAnimation(STAND_DOWN);
			}
			else {
				timeAnimation += deltaTime;
				while(timeAnimation > animations[currentAnimation].millisecsPerKeyframe)
				{
					timeAnimation -= animations[currentAnimation].millisecsPerKeyframe;
					currentKeyframe = (currentKeyframe + 1) % animations[currentAnimation].keyframeDispl.size();
				}
				texCoordDispl = animations[currentAnimation].keyframeDispl[currentKeyframe];
			}
			
		}
	}
}

void Sprite::render() const
{
	glm::mat4 modelview = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 0.f));
	shaderProgram->setUniformMatrix4f("modelview", modelview);
	shaderProgram->setUniform2f("texCoordDispl", texCoordDispl.x, texCoordDispl.y);
	glEnable(GL_TEXTURE_2D);
	texture->use();
	glBindVertexArray(vao);
	glEnableVertexAttribArray(posLocation);
	glEnableVertexAttribArray(texCoordLocation);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisable(GL_TEXTURE_2D);
}

void Sprite::free()
{
	glDeleteBuffers(1, &vbo);
}

void Sprite::setNumberAnimations(int nAnimations)
{
	animations.clear();
	animations.resize(nAnimations);
}

void Sprite::setAnimationSpeed(int animId, int keyframesPerSec)
{
	if(animId < int(animations.size()))
		animations[animId].millisecsPerKeyframe = 1000.f / keyframesPerSec;
}

void Sprite::addKeyframe(int animId, const glm::vec2 &displacement)
{
	if(animId < int(animations.size()))
		animations[animId].keyframeDispl.push_back(displacement);
}

void Sprite::changeAnimation(int animId)
{
	if(animId < int(animations.size()))
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

int Sprite::animation() const
{
	return currentAnimation;
}

void Sprite::setPosition(const glm::vec2 &pos)
{
	position = pos;
}



