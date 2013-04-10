#include "Camera.h"

Camera::Camera( glm::vec3& pos, glm::vec3& lookAt, glm::vec3& up )
{
	m_pitch = 0;
	m_ori = glm::lookAt(pos,lookAt,up);
	m_pos = pos;
	m_up = up;
	m_dir = glm::normalize(lookAt - pos);
}


Camera::~Camera(void)
{
}

void Camera::Update( float dt )
{
	m_ori = glm::lookAt(m_pos, m_pos + m_dir, m_up);
}

void Camera::Translate( glm::vec3& direction )
{
	m_pos += direction;
}

void Camera::Rotate( float angle, glm::vec3& axis )
{
	m_dir = glm::rotate(m_dir, angle, axis);

}
