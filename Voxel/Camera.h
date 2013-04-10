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

	void Update(float dt);
	void Rotate(float angle, glm::vec3& axis);
	void Translate(glm::vec3& direction);

	glm::vec3& GetPos(){return m_pos;}
	glm::vec3& GetDir(){return m_dir;}
	glm::vec3& GetUp(){return m_up;}
	glm::vec3 GetSide(){return glm::cross(m_dir, m_up);}

	glm::mat4x4& GetOri(){return m_ori;}
private:
	float m_pitch;
	glm::mat4x4 m_ori;
	glm::vec3 m_pos;
	glm::vec3 m_dir;
	glm::vec3 m_up;
};

#endif
