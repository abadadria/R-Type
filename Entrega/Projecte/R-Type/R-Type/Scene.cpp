#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"
#include "Camera.h"


Scene::Scene() {}

Scene::~Scene() {}


void Scene::init()
{
	initShaders();
	glm::vec2 cameraPos = glm::vec2(0.f, 0.f);
	glm::vec2 cameraSize = glm::vec2(float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1));
	glm::vec2 cameraSpeed = glm::vec2(1.f, 0.f);
	projection = glm::ortho(cameraPos.x, cameraPos.x + cameraSize.x, cameraPos.y + cameraSize.y, cameraPos.y);
	camera = Camera::getInstance();
	camera->init(cameraPos, cameraSize, cameraSpeed);
	currentTime = 0.0f;

	spritesheetBackground.loadFromFile("images/space_backgroundSmall.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spriteBackground = Sprite::createSprite(glm::ivec2(3247, 544), glm::vec2(1, 1), &spritesheetBackground, &texProgram);
	spriteBackground->setPosition(glm::ivec2(0, 0));
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	Camera* cam = Camera::getInstance();
	glm::ivec2 posCamera = cam->getPos();
	spriteBackground->setPosition(glm::ivec2(posCamera.x / 1.55, posCamera.y / 1.55));
}

void Scene::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if (!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}
