#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "ShootingEntity.h"


class Player : public ShootingEntity
{
	
public:;

	  void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) override; // Abstract method
	  void update(int deltaTime, glm::vec2 cameraPos, glm::vec2 cameraSize) override;


private:
	const glm::ivec2 movVecShooting = glm::ivec2(7, 0);
	const glm::ivec2 sizeSpriteShooting = glm::ivec2(32, 16);
	const glm::vec2 posShootingInSprite = glm::vec2(0.25, 0.5);
	const string shootingSpriteFile = "images/shootingShip.png";
	const glm::ivec2 sizeSpriteBeam = glm::ivec2(128, 32);
	const glm::vec2 posBeamInSprite = glm::vec2(0.5, 0.5);
	const string beamSpriteFile = "images/beamShip.png";
	int beamCharger = 0;
};


#endif // _PLAYER_INCLUDE


