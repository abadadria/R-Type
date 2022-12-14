#pragma once
#include "PassiveEntity.h"
class ForceMissile : public PassiveEntity
{

public:
	void init(ShaderProgram& shaderProgram, TileMap* tileMap) override;
	void update(int deltaTime, SceneLevel* scene) override;
	void render() override;
	void kill() override;

	string getType() const override;
	int getDamage() const override;
	void setPosition(const glm::vec2& pos) override;
	void doCollision(Entity* entity, SceneLevel* scene);

private:
	glm::ivec2 flamesSize;
	Sprite* spriteFlames;
	Texture spritesheetFlames;
};

