#include "pch.h"
#include "InspectorPreview.h"
#include "DisplayObject.h"
#include <string>
#include "Game.h"
using namespace DirectX;
using namespace DirectX::SimpleMath;

using Microsoft::WRL::ComPtr;

InspectorPreview::InspectorPreview()
{
	m_deviceResources = std::make_unique<DX::DeviceResources>();
	m_deviceResources->RegisterDeviceNotify(this);
	m_displayList.clear();

	camera.init();

	m_yaw = 0.0f;
	m_pitch = 0.0f;

	m_rotSensitivity = 0.01f;

	firstMouse = false;
}


InspectorPreview::~InspectorPreview()
{
#ifdef DXTK_AUDIO
	if (m_audEngine)
	{
		m_audEngine->Suspend();
	}
#endif
}

void InspectorPreview::Initialize(HWND window, int width, int height)
{

	m_deviceResources->SetWindow(window, width, height);

	m_deviceResources->CreateDeviceResources();
	CreateDeviceDependentResources();

	m_deviceResources->CreateWindowSizeDependentResources();
	CreateWindowSizeDependentResources();

	GetClientRect(window, &m_screenDimensions);
	int i = 0;


#ifdef DXTK_AUDIO
	// Create DirectXTK for Audio objects
	AUDIO_ENGINE_FLAGS eflags = AudioEngine_Default;
#ifdef _DEBUG
	eflags = eflags | AudioEngine_Debug;
#endif

	m_audEngine = std::make_unique<AudioEngine>(eflags);

	m_audioEvent = 0;
	m_audioTimerAcc = 10.f;
	m_retryDefault = false;

	m_waveBank = std::make_unique<WaveBank>(m_audEngine.get(), L"adpcmdroid.xwb");

	m_soundEffect = std::make_unique<SoundEffect>(m_audEngine.get(), L"MusicMono_adpcm.wav");
	m_effect1 = m_soundEffect->CreateInstance();
	m_effect2 = m_waveBank->CreateInstance(10);

	m_effect1->Play(true);
	m_effect2->Play();
#endif
}

#pragma region Frame Update
void InspectorPreview::Tick()
{	

	m_timer.Tick([&]()
	{
		Update(m_timer);
	});

	manageInput();

#ifdef DXTK_AUDIO
	// Only update audio engine once per frame
	if (!m_audEngine->IsCriticalError() && m_audEngine->Update())
	{
		// Setup a retry in 1 second
		m_audioTimerAcc = 1.f;
		m_retryDefault = true;
	}
#endif

	Render();
}


void InspectorPreview::Update(DX::StepTimer const & timer)
{
	Vector3 planarMotionVector = camera.getLookDirection();
	planarMotionVector.y = 0.0;

	camera.update();
	m_camPosition = camera.getCamPosition();

	m_view = Matrix::CreateLookAt(camera.getCamPosition(), camera.getCamLookAt(), -camera.getCamUp());

	m_batchEffect->SetView(m_view);
	m_batchEffect->SetWorld(Matrix::Identity);

	if (m_selectedObjects->size() != 1) {

		m_yaw = 0.0f;
		m_pitch = 0.0f;

	}
	//m_displayChunk.m_terrainEffect->SetView(m_view);
	//m_displayChunk.m_terrainEffect->SetWorld(Matrix::Identity);

	

#ifdef DXTK_AUDIO
	m_audioTimerAcc -= (float)timer.GetElapsedSeconds();
	if (m_audioTimerAcc < 0)
	{
		if (m_retryDefault)
		{
			m_retryDefault = false;
			if (m_audEngine->Reset())
			{
				// Restart looping audio
				m_effect1->Play(true);
			}
		}
		else
		{
			m_audioTimerAcc = 4.f;

			m_waveBank->Play(m_audioEvent++);

			if (m_audioEvent >= 11)
				m_audioEvent = 0;
		}
	}
#endif
}

void InspectorPreview::manageInput()
{
	if (*m_mouseInWindow == true) {

		if (firstMouse)
		{
			m_lastX = m_inputCommands->mouseX;
			m_lastY = m_inputCommands->mouseY;
			firstMouse = false;
		}

		float xOffset = (m_inputCommands->mouseX - m_lastX);
		float yOffset = (m_inputCommands->mouseY - m_lastY);

		m_lastX = m_inputCommands->mouseX;
		m_lastY = m_inputCommands->mouseY;

		if (m_inputCommands->mouseLeft == true) {

			if (m_inputCommands->mouseLeft == true) {
			
				xOffset *= m_rotSensitivity;
				yOffset *= m_rotSensitivity;
			
				m_yaw += xOffset;
				m_pitch -= yOffset;

			}
		}
	
	}
}
#pragma endregion

#pragma region Frame Render
// Draws the scene.
void InspectorPreview::Render()
{
	// Don't try to render anything before the first Update.
	if (m_timer.GetFrameCount() == 0)
	{
		return;
	}

	Clear();

	m_deviceResources->PIXBeginEvent(L"Render");
	auto context = m_deviceResources->GetD3DDeviceContext();

	
	m_deviceResources->PIXBeginEvent(L"Draw model");
	const XMVECTORF32 scale = { 1.0, 1.0, 1.0};
	const XMVECTORF32 translate = {0.0f, 0.0f, 0.0f };
	//convert degrees into radians for rotation matrix
	XMVECTOR rotate = Quaternion::CreateFromYawPitchRoll(0.0f, 0.0f, 0.0f);

	if (m_selectedObjects->size() == 1) 
		rotate = Quaternion::CreateFromYawPitchRoll(m_yaw, m_pitch, 0.0f);
	

	XMMATRIX local = m_world * XMMatrixTransformation(g_XMZero, Quaternion::Identity, scale, g_XMZero, rotate, translate);

	if (m_selectedObjects->size() == 1) {
		m_displayList[m_selectedObjects->at(0)].m_model->Draw(context, *m_states, local, m_view, m_projection, false);
	}

	m_deviceResources->PIXEndEvent();
	
	m_deviceResources->PIXEndEvent();


	m_deviceResources->Present();
}

void InspectorPreview::Clear()
{
	m_deviceResources->PIXBeginEvent(L"Clear");

	// Clear the views.
	auto context = m_deviceResources->GetD3DDeviceContext();
	auto renderTarget = m_deviceResources->GetBackBufferRenderTargetView();
	auto depthStencil = m_deviceResources->GetDepthStencilView();

	context->ClearRenderTargetView(renderTarget, Colors::CornflowerBlue);
	context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	context->OMSetRenderTargets(1, &renderTarget, depthStencil);

	// Set the viewport.
	auto viewport = m_deviceResources->GetScreenViewport();
	context->RSSetViewports(1, &viewport);

	m_deviceResources->PIXEndEvent();
}
#pragma endregion

#pragma region Message Handlers
// Message handlers
void InspectorPreview::OnActivated()
{
}

void InspectorPreview::OnDeactivated()
{
}

void InspectorPreview::OnSuspending()
{
#ifdef DXTK_AUDIO
	m_audEngine->Suspend();
#endif
}

void InspectorPreview::OnResuming()
{
	m_timer.ResetElapsedTime();

#ifdef DXTK_AUDIO
	m_audEngine->Resume();
#endif
}

void InspectorPreview::OnWindowSizeChanged(int width, int height)
{
	if (!m_deviceResources->WindowSizeChanged(width, height))
		return;

	CreateWindowSizeDependentResources();
}

void InspectorPreview::BuildDisplayList(std::vector<SceneObject>* SceneGraph)
{
	auto device = m_deviceResources->GetD3DDevice();
	auto devicecontext = m_deviceResources->GetD3DDeviceContext();

	if (!m_displayList.empty())		//is the vector empty
	{
		m_displayList.clear();		//if not, empty it
	}

	//for every item in the scenegraph
	int numObjects = SceneGraph->size();
	for (int i = 0; i < numObjects; i++)
	{

		//create a temp display object that we will populate then append to the display list.
		DisplayObject newDisplayObject;

		//load model
		std::wstring modelwstr = StringToWCHART(SceneGraph->at(i).model_path);							//convect string to Wchar
		newDisplayObject.m_model = Model::CreateFromCMO(device, modelwstr.c_str(), *m_fxFactory, true);	//get DXSDK to load model "False" for LH coordinate system (maya)

		//Load Texture
		std::wstring texturewstr = StringToWCHART(SceneGraph->at(i).tex_diffuse_path);								//convect string to Wchar
		HRESULT rs;
		rs = CreateDDSTextureFromFile(device, texturewstr.c_str(), nullptr, &newDisplayObject.m_texture_diffuse);	//load tex into Shader resource

		//if texture fails.  load error default
		if (rs)
		{
			CreateDDSTextureFromFile(device, L"database/data/Error.dds", nullptr, &newDisplayObject.m_texture_diffuse);	//load tex into Shader resource
		}

		//apply new texture to models effect
		newDisplayObject.m_model->UpdateEffects([&](IEffect* effect) //This uses a Lambda function,  if you dont understand it: Look it up.
		{
			auto lights = dynamic_cast<BasicEffect*>(effect);
			if (lights)
			{
				lights->SetTexture(newDisplayObject.m_texture_diffuse);
			}
		});

		newDisplayObject.m_name = SceneGraph->at(i).name;

		//set position
		newDisplayObject.m_position.x = SceneGraph->at(i).posX;
		newDisplayObject.m_position.y = SceneGraph->at(i).posY;
		newDisplayObject.m_position.z = SceneGraph->at(i).posZ;

		//setorientation
		newDisplayObject.m_orientation.x = SceneGraph->at(i).rotX;
		newDisplayObject.m_orientation.y = SceneGraph->at(i).rotY;
		newDisplayObject.m_orientation.z = SceneGraph->at(i).rotZ;

		//set scale
		newDisplayObject.m_scale.x = SceneGraph->at(i).scaX;
		newDisplayObject.m_scale.y = SceneGraph->at(i).scaY;
		newDisplayObject.m_scale.z = SceneGraph->at(i).scaZ;

		//set wireframe / render flags
		newDisplayObject.m_render = SceneGraph->at(i).editor_render;
		newDisplayObject.m_wireframe = SceneGraph->at(i).editor_wireframe;

		newDisplayObject.m_light_type = SceneGraph->at(i).light_type;
		newDisplayObject.m_light_diffuse_r = SceneGraph->at(i).light_diffuse_r;
		newDisplayObject.m_light_diffuse_g = SceneGraph->at(i).light_diffuse_g;
		newDisplayObject.m_light_diffuse_b = SceneGraph->at(i).light_diffuse_b;
		newDisplayObject.m_light_specular_r = SceneGraph->at(i).light_specular_r;
		newDisplayObject.m_light_specular_g = SceneGraph->at(i).light_specular_g;
		newDisplayObject.m_light_specular_b = SceneGraph->at(i).light_specular_b;
		newDisplayObject.m_light_spot_cutoff = SceneGraph->at(i).light_spot_cutoff;
		newDisplayObject.m_light_constant = SceneGraph->at(i).light_constant;
		newDisplayObject.m_light_linear = SceneGraph->at(i).light_linear;
		newDisplayObject.m_light_quadratic = SceneGraph->at(i).light_quadratic;

		//Initialization of added values
		newDisplayObject.m_X_Pos_Slider_Offset = 0.0f;
		newDisplayObject.m_Y_Pos_Slider_Offset = 0.0f;
		newDisplayObject.m_Z_Pos_Slider_Offset = 0.0f;

		newDisplayObject.m_X_Rot_Slider_Offset = 0.0f;
		newDisplayObject.m_Y_Rot_Slider_Offset = 0.0f;
		newDisplayObject.m_Z_Rot_Slider_Offset = 0.0f;

		newDisplayObject.m_X_Scale_Slider_Offset = 0.0f;
		newDisplayObject.m_Y_Scale_Slider_Offset = 0.0f;
		newDisplayObject.m_Z_Scale_Slider_Offset = 0.0f;

		m_displayList.push_back(newDisplayObject);

	}
}

void InspectorPreview::updateDisplayList(SceneObject newSceneObject)
{
	auto device = m_deviceResources->GetD3DDevice();
	auto devicecontext = m_deviceResources->GetD3DDeviceContext();

	//create a temp display object that we will populate then append to the display list.
	DisplayObject newDisplayObject;

	//load model
	std::wstring modelwstr = StringToWCHART(newSceneObject.model_path);							//convect string to Wchar
	newDisplayObject.m_model = Model::CreateFromCMO(device, modelwstr.c_str(), *m_fxFactory, true);	//get DXSDK to load model "False" for LH coordinate system (maya)

	//Load Texture
	std::wstring texturewstr = StringToWCHART(newSceneObject.tex_diffuse_path);								//convect string to Wchar
	HRESULT rs;
	rs = CreateDDSTextureFromFile(device, texturewstr.c_str(), nullptr, &newDisplayObject.m_texture_diffuse);	//load tex into Shader resource

	//if texture fails.  load error default
	if (rs)
	{
		CreateDDSTextureFromFile(device, L"database/data/Error.dds", nullptr, &newDisplayObject.m_texture_diffuse);	//load tex into Shader resource
	}

	//apply new texture to models effect
	newDisplayObject.m_model->UpdateEffects([&](IEffect* effect) //This uses a Lambda function,  if you dont understand it: Look it up.
	{
		auto lights = dynamic_cast<BasicEffect*>(effect);
		if (lights)
		{
			lights->SetTexture(newDisplayObject.m_texture_diffuse);
		}
	});

	//set position
	newDisplayObject.m_position.x = newSceneObject.posX;
	newDisplayObject.m_position.y = newSceneObject.posY;
	newDisplayObject.m_position.z = newSceneObject.posZ;

	//setorientation
	newDisplayObject.m_orientation.x = newSceneObject.rotX;
	newDisplayObject.m_orientation.y = newSceneObject.rotY;
	newDisplayObject.m_orientation.z = newSceneObject.rotZ;

	//set scale
	newDisplayObject.m_scale.x = newSceneObject.scaX;
	newDisplayObject.m_scale.y = newSceneObject.scaY;
	newDisplayObject.m_scale.z = newSceneObject.scaZ;

	//set wireframe / render flags
	newDisplayObject.m_render = newSceneObject.editor_render;
	newDisplayObject.m_wireframe = newSceneObject.editor_wireframe;

	newDisplayObject.m_light_type = newSceneObject.light_type;
	newDisplayObject.m_light_diffuse_r = newSceneObject.light_diffuse_r;
	newDisplayObject.m_light_diffuse_g = newSceneObject.light_diffuse_g;
	newDisplayObject.m_light_diffuse_b = newSceneObject.light_diffuse_b;
	newDisplayObject.m_light_specular_r = newSceneObject.light_specular_r;
	newDisplayObject.m_light_specular_g = newSceneObject.light_specular_g;
	newDisplayObject.m_light_specular_b = newSceneObject.light_specular_b;
	newDisplayObject.m_light_spot_cutoff = newSceneObject.light_spot_cutoff;
	newDisplayObject.m_light_constant = newSceneObject.light_constant;
	newDisplayObject.m_light_linear = newSceneObject.light_linear;
	newDisplayObject.m_light_quadratic = newSceneObject.light_quadratic;

	//Initialization of added values
	newDisplayObject.m_X_Pos_Slider_Offset = 0.0f;
	newDisplayObject.m_Y_Pos_Slider_Offset = 0.0f;
	newDisplayObject.m_Z_Pos_Slider_Offset = 0.0f;

	newDisplayObject.m_X_Rot_Slider_Offset = 0.0f;
	newDisplayObject.m_Y_Rot_Slider_Offset = 0.0f;
	newDisplayObject.m_Z_Rot_Slider_Offset = 0.0f;

	newDisplayObject.m_X_Scale_Slider_Offset = 0.0f;
	newDisplayObject.m_Y_Scale_Slider_Offset = 0.0f;
	newDisplayObject.m_Z_Scale_Slider_Offset = 0.0f;

	m_displayList.push_back(newDisplayObject);
}

#pragma region Direct3D Resources
// These are the resources that depend on the device.
void InspectorPreview::CreateDeviceDependentResources()
{
	auto context = m_deviceResources->GetD3DDeviceContext();
	auto device = m_deviceResources->GetD3DDevice();

	m_states = std::make_unique<CommonStates>(device);

	m_fxFactory = std::make_unique<EffectFactory>(device);
	m_fxFactory->SetDirectory(L"database/data/"); //fx Factory will look in the database directory
	m_fxFactory->SetSharing(false);	//we must set this to false otherwise it will share effects based on the initial tex loaded (When the model loads) rather than what we will change them to.

	m_sprites = std::make_unique<SpriteBatch>(context);

	m_batch = std::make_unique<PrimitiveBatch<VertexPositionColor>>(context);

	m_batchEffect = std::make_unique<BasicEffect>(device);
	m_batchEffect->SetVertexColorEnabled(true);

	{
		void const* shaderByteCode;
		size_t byteCodeLength;

		m_batchEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

		DX::ThrowIfFailed(
			device->CreateInputLayout(VertexPositionColor::InputElements,
				VertexPositionColor::InputElementCount,
				shaderByteCode, byteCodeLength,
				m_batchInputLayout.ReleaseAndGetAddressOf())
		);
	}

	m_font = std::make_unique<SpriteFont>(device, L"SegoeUI_18.spritefont");

	//    m_shape = GeometricPrimitive::CreateTeapot(context, 4.f, 8);

		// SDKMESH has to use clockwise winding with right-handed coordinates, so textures are flipped in U
	m_model = Model::CreateFromSDKMESH(device, L"tiny.sdkmesh", *m_fxFactory);


	// Load textures
	DX::ThrowIfFailed(
		CreateDDSTextureFromFile(device, L"seafloor.dds", nullptr, m_texture1.ReleaseAndGetAddressOf())
	);

	DX::ThrowIfFailed(
		CreateDDSTextureFromFile(device, L"windowslogo.dds", nullptr, m_texture2.ReleaseAndGetAddressOf())
	);
}

void InspectorPreview::CreateWindowSizeDependentResources()
{
	auto size = m_deviceResources->GetOutputSize();
	float aspectRatio = float(size.right) / float(size.bottom);
	float fovAngleY = 70.0f * XM_PI / 180.0f;

	// This is a simple example of change that can be made when the app is in
	// portrait or snapped view.
	if (aspectRatio < 1.0f)
	{
		fovAngleY *= 2.0f;
	}

	// This sample makes use of a right-handed coordinate system using row-major matrices.
	m_projection = Matrix::CreatePerspectiveFieldOfView(
		fovAngleY,
		aspectRatio,
		0.01f,
		1000.0f
	);

	m_batchEffect->SetProjection(m_projection);
}

void InspectorPreview::OnDeviceLost()
{
	m_states.reset();
	m_fxFactory.reset();
	m_sprites.reset();
	m_batch.reset();
	m_batchEffect.reset();
	m_font.reset();
	m_shape.reset();
	m_model.reset();
	m_texture1.Reset();
	m_texture2.Reset();
	m_batchInputLayout.Reset();
}

void InspectorPreview::OnDeviceRestored()
{
	CreateDeviceDependentResources();

	CreateWindowSizeDependentResources();
}
#pragma endregion
