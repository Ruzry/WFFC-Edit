#include "MFCMain.h"
#include "resource.h"


BEGIN_MESSAGE_MAP(MFCMain, CWinApp)
	ON_COMMAND(ID_FILE_QUIT,	&MFCMain::MenuFileQuit)
	ON_COMMAND(ID_FILE_SAVETERRAIN, &MFCMain::MenuFileSaveTerrain)
	/*ON_COMMAND(ID_FILE_TEST, &MFCMain::MenuFileTest)*/
	ON_COMMAND(ID_EDIT_SELECT, &MFCMain::MenuEditSelect)
	ON_COMMAND(ID_BUTTON40001,	&MFCMain::ToolBarButton1)
	ON_COMMAND(ID_FILE_SAVEOBJECTS, &MFCMain::MenuFileSaveObjects)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_TOOL, &CMyFrame::OnUpdatePage)
END_MESSAGE_MAP()

BOOL MFCMain::InitInstance()
{
	//instanciate the mfc frame
	m_frame = new CMyFrame();
	m_pMainWnd = m_frame;

	m_frame->Create(	NULL,
					_T("World Of Flim-Flam Craft Editor"),
					WS_OVERLAPPEDWINDOW,
					CRect(100, 100, 1024, 768),
					NULL,
					NULL,
					0,
					NULL
				);

	//show and set the window to run and update. 
	m_frame->ShowWindow(SW_SHOW);
	m_frame->UpdateWindow();


	//get the rect from the MFC window so we can get its dimensions
	m_toolHandle = m_frame->m_DirXView.GetSafeHwnd();				//handle of directX child window
	m_frame->m_DirXView.GetClientRect(&WindowRECT);
	m_width		= WindowRECT.Width();
	m_height	= WindowRECT.Height();

	m_ToolSystem.onActionInitialise(m_toolHandle, m_width, m_height);

	m_InspectorDialogue.Create(IDD_DIALOG2);	//Start up modeless
	m_InspectorDialogue.initializeConnection(&m_ToolSystem, m_ToolSystem.getDisplayList(), m_ToolSystem.getSelectedObjects());
	m_InspectorDialogue.ShowWindow(SW_SHOW);	//show modeless

	

	return TRUE;
}

int MFCMain::Run()
{
	MSG msg;
	BOOL bGotMsg;

	PeekMessage(&msg, NULL, 0U, 0U, PM_NOREMOVE);

	while (WM_QUIT != msg.message)
	{
		if (true)
		{
			bGotMsg = (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE) != 0);
		}
		else
		{
			bGotMsg = (GetMessage(&msg, NULL, 0U, 0U) != 0);
		}

		if (bGotMsg)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			m_ToolSystem.UpdateInput(&msg);
		}
		else
		{	
			int ID = m_ToolSystem.getCurrentSelectionID();
			std::wstring statusString = L"Camera Position: X: " + std::to_wstring(m_ToolSystem.m_camX) + L" Y: " 
															+ std::to_wstring(m_ToolSystem.m_camY) + L" Z: "
															+ std::to_wstring(m_ToolSystem.m_camZ);
			m_ToolSystem.Tick(&msg);
			
			m_InspectorDialogue.update();
			
			//send current object ID to status bar in The main frame
			m_frame->m_wndStatusBar.SetPaneText(1, statusString.c_str(), 1);	
		}
	}

	return (int)msg.wParam;
}

void MFCMain::MenuFileQuit()
{
	//will post message to the message thread that will exit the application normally
	PostQuitMessage(0);
}

void MFCMain::MenuFileSaveTerrain()
{
	m_ToolSystem.onActionSaveTerrain();
}

void MFCMain::MenuEditSelect()
{
	//SelectDialogue m_ToolSelectDialogue(NULL, &m_ToolSystem.m_sceneGraph);		//create our dialoguebox //modal constructor
	//m_ToolSelectDialogue.DoModal();	// start it up modal

	//modeless dialogue must be declared in the class.   If we do local it will go out of scope instantly and destroy itself
	m_ToolSelectDialogue.Create(IDD_DIALOG1);	//Start up modeless
	m_ToolSelectDialogue.ShowWindow(SW_SHOW);	//show modeless
	m_ToolSelectDialogue.SetObjectData(&m_ToolSystem.m_sceneGraph, m_ToolSystem.getDisplayList(), m_ToolSystem.m_selectedObjects, m_ToolSystem.getSelected());
}

void MFCMain::MenuFileTest()
{
}

void MFCMain::MenuFileSaveObjects()
{
	//Reset Inspector position values as save move them to the actual value rather than just an offset;
	m_InspectorDialogue.resetSliders();
	m_ToolSystem.onActionSave();
}

void MFCMain::ToolBarButton1()
{
	SceneObject newSceneObject;

	newSceneObject.model_path = "database/data/placeholder.cmo";
	newSceneObject.tex_diffuse_path = "database/data/placeholder.dds";

	newSceneObject.posX = 0.0f;
	newSceneObject.posY = 0.0f;
	newSceneObject.posZ = 0.0f;

	newSceneObject.rotX = 0.0f;
	newSceneObject.rotY = 0.0f;
	newSceneObject.rotZ = 0.0f;

	newSceneObject.scaX = 1.0f;
	newSceneObject.scaY = 1.0f;
	newSceneObject.scaZ = 1.0f;

	newSceneObject.render = true;
	newSceneObject.collision = true;
	newSceneObject.collision_mesh = "";
	newSceneObject.collectable = false;
	newSceneObject.destructable = false;
	newSceneObject.health_amount = 0;
	newSceneObject.editor_render = true;
	newSceneObject.editor_texture_vis = false;
	newSceneObject.editor_normals_vis = false;
	newSceneObject.editor_collision_vis = false;
	newSceneObject.editor_pivot_vis = false;
	newSceneObject.pivotX = 0;
	newSceneObject.pivotY = 0;
	newSceneObject.pivotZ = 0;
	newSceneObject.snapToGround = false;
	newSceneObject.AINode = false;
	newSceneObject.audio_path = "";
	newSceneObject.volume = 100.0f;
	newSceneObject.pitch = 0.0f;
	newSceneObject.pan = 0.0f;
	newSceneObject.one_shot = false;
	newSceneObject.play_on_init = false;
	newSceneObject.play_in_editor = false;
	newSceneObject.min_dist = 100.f;
	newSceneObject.max_dist = 0.0f;
	newSceneObject.camera = false;
	newSceneObject.path_node = false;
	newSceneObject.path_node_start = false;
	newSceneObject.path_node_end = false;
	newSceneObject.parent_id = -1;
	newSceneObject.editor_wireframe = false;
	newSceneObject.name = "";

	newSceneObject.light_type = 0;
	newSceneObject.light_diffuse_r = 0.0f;
	newSceneObject.light_diffuse_g = 0.0f;
	newSceneObject.light_diffuse_b = 0.0f;
	newSceneObject.light_specular_r = 0.0f;
	newSceneObject.light_specular_g = 0.0f;
	newSceneObject.light_specular_b = 0.0f;
	newSceneObject.light_spot_cutoff = 0.0f;
	newSceneObject.light_constant = 0.0f;
	newSceneObject.light_linear = 0.0f;
	newSceneObject.light_quadratic = 0.0f;

	m_ToolSystem.addToSceneGraph(newSceneObject);

}


MFCMain::MFCMain()
{
}


MFCMain::~MFCMain()
{
}
