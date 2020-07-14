#include "DisplayObject.h"

DisplayObject::DisplayObject()
{
	m_model = NULL;
	m_texture_diffuse = NULL;
	m_orientation.x = 0.0f;
	m_orientation.y = 0.0f;
	m_orientation.z = 0.0f;
	m_position.x = 0.0f;
	m_position.y = 0.0f;
	m_position.z = 0.0f;
	m_scale.x = 0.0f;
	m_scale.y = 0.0f;
	m_scale.z = 0.0f;
	m_render = true;
	m_wireframe = false;

	m_light_type =0;
	m_light_diffuse_r = 0.0f;	m_light_diffuse_g = 0.0f;	m_light_diffuse_b = 0.0f;
	m_light_specular_r = 0.0f;	m_light_specular_g = 0.0f;	m_light_specular_b = 0.0f;
	m_light_spot_cutoff = 0.0f;
	m_light_constant = 0.0f;
	m_light_linear = 0.0f;
	m_light_quadratic = 0.0f;
}


DisplayObject::~DisplayObject()
{
//	delete m_texture_diffuse;
}

void DisplayObject::applyOffsetValues()
{
	m_position.x += m_X_Pos_Slider_Offset;
	m_position.y += m_Y_Pos_Slider_Offset;
	m_position.z += m_Z_Pos_Slider_Offset;

	m_X_Pos_Slider_Offset = 0;
	m_Y_Pos_Slider_Offset = 0;
	m_Z_Pos_Slider_Offset = 0;

	m_scale.x += m_X_Scale_Slider_Offset;
	m_scale.y += m_Y_Scale_Slider_Offset;
	m_scale.z += m_Z_Scale_Slider_Offset;

	m_X_Scale_Slider_Offset = 0;
	m_Y_Scale_Slider_Offset = 0;
	m_Z_Scale_Slider_Offset = 0;

	m_orientation.x += m_X_Rot_Slider_Offset;
	m_orientation.y += m_Y_Rot_Slider_Offset;
	m_orientation.z += m_Z_Rot_Slider_Offset;

	m_X_Rot_Slider_Offset = 0;
	m_Y_Rot_Slider_Offset = 0;
	m_Z_Rot_Slider_Offset = 0;
}
