#ifndef _SPRITE_INCLUDE
#define _SPRITE_INCLUDE


#include <vector>
#include <glm/glm.hpp>
#include "Texture.h"
#include "ShaderProgram.h"
#include "AnimKeyframes.h"


// This class is derived from code seen earlier in TexturedQuad but it is also
// able to manage animations stored as a spritesheet. 


class Sprite
{

protected:
	Sprite(const glm::vec2 &quadSize, const glm::vec2 &sizeInSpritesheet, Texture *spritesheet, ShaderProgram *program);
	
	void continueAnimation(int deltaTime, bool ascending, bool loop);

public:
	~Sprite();

	// Textured quads can only be created inside an OpenGL context
	static Sprite *createSprite(const glm::vec2 &quadSize, const glm::vec2 &sizeInSpritesheet, Texture *spritesheet, ShaderProgram *program);

	virtual void update(int deltaTime);
	void render() const;
	void free();

	void setNumberAnimations(int nAnimations);
	void setAnimationSpeed(int animId, int keyframesPerSec);
	void setAnimationLooping(int animId, bool looping);
	void addKeyframe(int animId, const glm::vec2 &frame);
	virtual void changeAnimation(int animId);
	int animation() const;
	void setDisplayOffset(glm::vec2 offset);

	bool isAnimationFinished();
	
	void setPosition(const glm::vec2 &pos);

private:
	Texture *texture;
	ShaderProgram *shaderProgram;
	GLuint vao;
	GLuint vbo;
	GLint posLocation, texCoordLocation;
	glm::vec2 position;
	
protected:
	int currentAnimation, currentKeyframe;
	float timeAnimation;
	glm::vec2 texCoordDispl;
	vector<AnimKeyframes> animations;

};


#endif // _SPRITE_INCLUDE

