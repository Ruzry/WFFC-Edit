#pragma once
#include "DeviceResources.h"
#include "StepTimer.h"
#include "SceneObject.h"
#include "DisplayObject.h"
#include "InputCommands.h"
#include <vector>
#include "PreviewCamera.h"


class InspectorPreview :
	public DX::IDeviceNotify
{
public:
	InspectorPreview();
	~InspectorPreview();

	// Initialization and management
	void Initialize(HWND window, int width, int height);

	// Basic game loop
	void Tick();
	void Render();

	// Rendering helpers
	void Clear();

	// IDeviceNotify
	virtual void OnDeviceLost() override;
	virtual void OnDeviceRestored() override;

	// Messages
	void OnActivated();
	void OnDeactivated();
	void OnSuspending();
	void OnResuming();
	void OnWindowSizeChanged(int width, int height);


	void BuildDisplayList(std::vector<SceneObject> * SceneGraph); //note vector passed by reference 
	void updateDisplayList(SceneObject newSceneObject);

	void setSelectedObjects(std::vector<int>* selectedObjects) { m_selectedObjects = selectedObjects; }
	void setInputCommands(InputCommands* input) { m_inputCommands = input; }
	void setMouseInWindow(bool* flag) { m_mouseInWindow = flag; }

	void manageInput();

private:

	void Update(DX::StepTimer const& timer);
	void CreateDeviceDependentResources();
	void CreateWindowSizeDependentResources();

	//tool specific
	std::vector<DisplayObject>			m_displayList;
	InputCommands*						m_inputCommands;
	std::vector<int>*					m_selectedObjects;
	bool*								m_mouseInWindow;

	//functionality
	float								m_movespeed;
	RECT								m_screenDimensions;

	//camera
	PreviewCamera camera;

	//Object rotation
	float m_camRotRate, m_yaw, m_pitch, m_rotSensitivity, m_lastX, m_lastY;
	const float m_pi = 3.14159265359;
	bool firstMouse;

	// Device resources.
	std::shared_ptr<DX::DeviceResources>    m_deviceResources;

	// Rendering loop timer.
	DX::StepTimer                           m_timer;

	// DirectXTK objects.
	std::unique_ptr<DirectX::CommonStates>                                  m_states;
	std::unique_ptr<DirectX::BasicEffect>                                   m_batchEffect;
	std::unique_ptr<DirectX::EffectFactory>                                 m_fxFactory;
	std::unique_ptr<DirectX::GeometricPrimitive>                            m_shape;
	std::unique_ptr<DirectX::Model>                                         m_model;
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>>  m_batch;
	std::unique_ptr<DirectX::SpriteBatch>                                   m_sprites;
	std::unique_ptr<DirectX::SpriteFont>                                    m_font;

#ifdef DXTK_AUDIO
	std::unique_ptr<DirectX::AudioEngine>                                   m_audEngine;
	std::unique_ptr<DirectX::WaveBank>                                      m_waveBank;
	std::unique_ptr<DirectX::SoundEffect>                                   m_soundEffect;
	std::unique_ptr<DirectX::SoundEffectInstance>                           m_effect1;
	std::unique_ptr<DirectX::SoundEffectInstance>                           m_effect2;
#endif

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>                        m_texture1;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>                        m_texture2;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>                               m_batchInputLayout;

#ifdef DXTK_AUDIO
	uint32_t                                                                m_audioEvent;
	float                                                                   m_audioTimerAcc;

	bool                                                                    m_retryDefault;
#endif

	DirectX::SimpleMath::Matrix                                             m_world;
	DirectX::SimpleMath::Matrix                                             m_view;
	DirectX::SimpleMath::Matrix                                             m_projection;

	DirectX::SimpleMath::Vector3											m_camPosition;
};

