#pragma once

#include <d3d11.h>
#include <SimpleMath.h>
#include "InputCommands.h"

class PreviewCamera
{
public:
	PreviewCamera();
	~PreviewCamera();

	void init();
	void update(int* scrollVal);

	DirectX::SimpleMath::Vector3 getLookDirection() { return m_camLookDirection; }
	DirectX::SimpleMath::Vector3 getCamPosition() { return m_camPosition; }
	DirectX::SimpleMath::Vector3 getCamLookAt() { return m_camLookAt; }
	DirectX::SimpleMath::Vector3 getCamOrientation() { return m_camOrientation; }
	DirectX::SimpleMath::Vector3 getCamRight() { return m_camRight; }
	DirectX::SimpleMath::Vector3 getCamUp() { return m_camUp; }


private:

	float toRadians(float degrees);

	DirectX::SimpleMath::Vector3		m_camPosition;
	DirectX::SimpleMath::Vector3		m_camOrientation;
	DirectX::SimpleMath::Vector3		m_camLookAt;
	DirectX::SimpleMath::Vector3		m_camLookDirection;
	DirectX::SimpleMath::Vector3		m_camRight;
	DirectX::SimpleMath::Vector3		m_camUp;

	float m_camRotRate, m_yaw, m_pitch, m_cameraSensitivity, m_lastX, m_lastY;
	const float m_pi = 3.14159265359;

};

