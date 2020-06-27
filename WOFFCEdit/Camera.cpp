#include "Camera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::init()
{
	//camera
	m_camPosition.x = 0.0f;
	m_camPosition.y = 3.7f;
	m_camPosition.z = -3.5f;

	m_camOrientation.x = 0;
	m_camOrientation.y = 0;
	m_camOrientation.z = 0;

	m_camLookAt.x = 0.0f;
	m_camLookAt.y = 0.0f;
	m_camLookAt.z = 0.0f;

	m_camLookDirection.x = 0.0f;
	m_camLookDirection.y = 0.0f;
	m_camLookDirection.z = 0.0f;

	m_camRight.x = 0.0f;
	m_camRight.y = 0.0f;
	m_camRight.z = 0.0f;

	m_camOrientation.x = 0.0f;
	m_camOrientation.y = 0.0f;
	m_camOrientation.z = 0.0f;

	m_camUp.x = 0.0f;
	m_camUp.y = 1.0f;
	m_camUp.z = 0.0f;

	m_camRotRate = 3.0;

	m_yaw = -90.0f;
	m_pitch = 0.0f;

	m_cameraSensitivity = 0.5f;

	firstMouse = true;

	
}

void Camera::update(InputCommands* input, float m_movespeed)
{

	if (input->rotRight)
	{
		m_camOrientation.y -= m_camRotRate;
	}
	if (input->rotLeft)
	{
		m_camOrientation.y += m_camRotRate;
	}

	//create look direction from Euler angles in m_camOrientation
	m_camLookDirection.x = sin((m_camOrientation.y)*m_pi / 180);
	m_camLookDirection.z = cos((m_camOrientation.y)*m_pi / 180);
	m_camLookDirection.Normalize();

	mouseMovement(input->mouseX, input->MouseY);

	//create right vector from look Direction
	m_camLookDirection.Cross(Vector3::UnitY, m_camRight);
	m_camLookDirection.Cross(m_camRight, m_camUp);
	
	//process input and update stuff
	if (input->forward)
	{
		m_camPosition += m_camLookDirection * m_movespeed;
	}
	if (input->back)
	{
		m_camPosition -= m_camLookDirection * m_movespeed;
	}
	if (input->right)
	{
		m_camPosition += m_camRight * m_movespeed;
	}
	if (input->left)
	{
		m_camPosition -= m_camRight * m_movespeed;
	}
	if (input->up) 
	{
		m_camPosition -= m_camUp * m_movespeed;
	}
	if (input->down) 
	{
		m_camPosition += m_camUp * m_movespeed;
	}

	//update lookat point
	m_camLookAt = m_camPosition + m_camLookDirection;

}

void Camera::mouseMovement(float xPos, float yPos)
{
	if (firstMouse)
	{
		m_lastX = xPos;
		m_lastY = yPos;
		firstMouse = false;
	}

	float xOffset = xPos - m_lastX;
	float yOffset = yPos - m_lastY;
	m_lastX = xPos;
	m_lastY = yPos;

	xOffset *= m_cameraSensitivity;
	yOffset *= m_cameraSensitivity;

	m_yaw += xOffset;
	m_pitch -= yOffset;


	if (m_pitch > 89.0f)
		m_pitch = 89.0f;
	if (m_pitch < -89.0f)
		m_pitch = -89.0f;

	m_camLookDirection.x = cos(toRadians(m_yaw)) * cos(toRadians(m_pitch));
	m_camLookDirection.y = sin(toRadians(m_pitch));
	m_camLookDirection.z = sin(toRadians(m_yaw)) * cos(toRadians(m_pitch));
	m_camLookDirection.Normalize();

	//cos
}

float Camera::toRadians(float degrees)
{
	float radians = (degrees * m_pi) / 180;


	return radians;
}
