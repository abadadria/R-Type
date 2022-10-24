#ifndef _CAMERA_INCLUDE
#define _CAMERA_INCLUDE


#include <glm/glm.hpp>
#include <mutex>
#include <glm/gtc/matrix_transform.hpp>


class Camera
{

public:
	static Camera* getInstance();

	void init(glm::vec2 pos, glm::vec2 size, glm::vec2 speed);
	glm::mat4 update();

	glm::vec2 getPos();
	glm::vec2 getSize();
	glm::vec2 getSpeed();

	void setPos(glm::vec2 pos);
	void setSpeed(glm::vec2 speed);

	bool collision(glm::vec2 entityPos, glm::vec2 entitySize, float margin);

	Camera(Camera& other) = delete;
	void operator=(const Camera&) = delete;

private:
	Camera();
	~Camera();

private:
	static Camera* instance;

	glm::vec2 cameraPos;
	glm::vec2 cameraSize;
	glm::vec2 cameraSpeed;

};

#endif //_CAMERA_INCLUDE
