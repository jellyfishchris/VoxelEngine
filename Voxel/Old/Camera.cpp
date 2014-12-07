#include "Camera.h"

Camera::Camera( glm::vec3& pos, glm::vec3& lookAt, glm::vec3& up )
	: m_yaw(0.0f), m_pitch(0.0f), m_pos(pos)
{
}


Camera::~Camera(void)
{
}

glm::mat4x4 Camera::Orientation()
{
	glm::mat4 ori;
	ori = glm::rotate(ori, m_pitch, glm::vec3(1,0,0));
	ori = glm::rotate(ori, m_yaw, glm::vec3(0,1,0));
	return ori;
}

void Camera::Translate( glm::vec3& direction )
{
	m_pos += direction;
}

void Camera::RotateX(float angle)
{
	if((m_pitch + angle <= 80) && (m_pitch + angle >= -80))
		m_pitch += angle;
}
void Camera::RotateY(float angle)
{
	m_yaw += angle;
	if(m_yaw / 360 >= 1)
		m_yaw = (float)((int) m_yaw % 360);
}