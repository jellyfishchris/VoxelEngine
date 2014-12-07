#ifndef CAMERA_H
#define CAMERA_H

#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

class Camera
{
public:
	Camera(glm::vec3& pos, glm::vec3& lookAt, glm::vec3& up);
	~Camera(void);

	glm::mat4x4 Orientation();

	void RotateX(float angle);
	void RotateY(float angle);
	void Translate(glm::vec3& direction);

	glm::vec3& GetPos(){return m_pos;}

	glm::vec3 Camera::Forward() {
		glm::vec4 forward = glm::inverse(Orientation()) * glm::vec4(0,0,-1,1);
		return glm::vec3(forward);
	}

	glm::vec3 Camera::Right() {
		glm::vec4 right = glm::inverse(Orientation()) * glm::vec4(1,0,0,1);
		return glm::vec3(right);
	}

	glm::vec3 Camera::Up() {
		glm::vec4 up = glm::inverse(Orientation()) * glm::vec4(0,1,0,1);
		return glm::vec3(up);
	}
	//glm::vec4 GetSide(){return glm::cross(m_dir, m_up);}

private:
	float m_pitch;
	float m_yaw;

	glm::vec3 m_pos;

	glm::vec4 m_dir;
	glm::vec4 m_up;
};

#endif
