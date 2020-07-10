#pragma once
#include "pch.h"


class DisplayObject
{
public:
	DisplayObject();
	~DisplayObject();

	std::shared_ptr<DirectX::Model>						m_model;							//main Mesh
	ID3D11ShaderResourceView *							m_texture_diffuse;					//diffuse texture


	int m_ID;
	DirectX::SimpleMath::Vector3			m_position;
	DirectX::SimpleMath::Vector3			m_orientation;
	DirectX::SimpleMath::Vector3			m_scale;
	bool									m_render;
	bool									m_wireframe;

	int		m_light_type;
	float	m_light_diffuse_r,	m_light_diffuse_g,	m_light_diffuse_b;
	float	m_light_specular_r, m_light_specular_g, m_light_specular_b;
	float	m_light_spot_cutoff;
	float	m_light_constant;
	float	m_light_linear;
	float	m_light_quadratic;



	float m_X_Pos_Slider_Offset, m_Y_Pos_Slider_Offset, m_Z_Pos_Slider_Offset;
	float m_X_Rot_Slider_Offset, m_Y_Rot_Slider_Offset, m_Z_Rot_Slider_Offset;
	float m_X_Scale_Slider_Offset, m_Y_Scale_Slider_Offset, m_Z_Scale_Slider_Offset;
};

