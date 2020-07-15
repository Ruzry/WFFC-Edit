#include "PreviewCamera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

PreviewCamera::PreviewCamera()
{
}


PreviewCamera::~PreviewCamera()
{
}

void PreviewCamera::init()
{
	//camera
	m_camPosition.x = 0.0f;
	m_camPosition.y = 0.0f;
	m_camPosition.z = -10.0f;

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

	m_yaw = 0.0f;
	m_pitch = 0.0f;

	m_cameraSensitivity = 0.5f;
}

void PreviewCamera::update(int* scrollVal)
{
	m_camPosition.z = *scrollVal - 10;

	//create look direction from Euler angles in m_camOrientation
	m_camLookDirection.x = sin((m_camOrientation.y)*m_pi / 180);
	m_camLookDirection.z = cos((m_camOrientation.y)*m_pi / 180);
	m_camLookDirection.Normalize();

	//create right vector from look Direction
	m_camLookDirection.Cross(Vector3::UnitY, m_camRight);
	m_camLookDirection.Cross(m_camRight, m_camUp);

	//update lookat point
	m_camLookAt = m_camPosition + m_camLookDirection;
}

float PreviewCamera::toRadians(float degrees)
{
	float radians = (degrees * m_pi) / 180;

	return radians;
}
