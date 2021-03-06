#pragma once

#include <afxext.h>
#include "pch.h"
#include "Game.h"
#include "sqlite3.h"
#include "SceneObject.h"
#include "InputCommands.h"
#include <vector>
#include "DisplayObject.h"
#include "MFCRenderFrame.h"


class ToolMain
{
public: //methods
	ToolMain();
	~ToolMain();

	//onAction - These are the interface to MFC
	int		getCurrentSelectionID();										//returns the selection number of currently selected object so that It can be displayed.
	void	onActionInitialise(HWND handle, CChildRender* mainFrame, int width, int height);			//Passes through handle and hieght and width and initialises DirectX renderer and SQL LITE
	void	onActionFocusCamera();
	void	onActionLoad();													//load the current chunk
	afx_msg	void	onActionSave();											//save the current chunk
	afx_msg void	onActionSaveTerrain();									//save chunk geometry

	void	Tick(MSG *msg);
	void	UpdateInput(MSG *msg);

public:	//variables
	std::vector<SceneObject>    m_sceneGraph;	//our scenegraph storing all the objects in the current chunk
	ChunkObject					m_chunk;		//our landscape chunk
	
	
	int m_selectedObject;		//ID of current Selection
	std::vector<int>* m_selectedObjects;
	CChildRender* m_mainRenderFrame;
	
	float m_camX, m_camY, m_camZ;

	std::vector<DisplayObject>* getDisplayList() { return m_DisplayList; }
	std::vector<int>* getSelectedObjects() { return m_selectedObjects; }
	std::vector<int>* getPreviousObjects() { return m_d3dRenderer.getPreviousIDs(); }
	InputCommands* getInputCommands() { return &m_toolInputCommands; }
	bool* getSelected() { return m_selected; }
	void setSelected(bool flag) { m_d3dRenderer.setSelected(flag); }


	bool addToSceneGraph(SceneObject newSceneObject);
	void removeObject(int objectID) { m_d3dRenderer.removeObject(objectID); }
	void updateSceneGraph();

private:	//methods
	void	onContentAdded();
	std::vector<DisplayObject>* m_DisplayList;
	
		
private:	//variables
	HWND*	m_toolHandle;		//Handle to the  window
	Game	m_d3dRenderer;		//Instance of D3D rendering system for our tool
	InputCommands m_toolInputCommands;		//input commands that we want to use and possibly pass over to the renderer
	CRect	WindowRECT;		//Window area rectangle. 
	char	m_keyArray[256];
	sqlite3 *m_databaseConnection;	//sqldatabase handle

	int m_width;		//dimensions passed to directX
	int m_height;
	int m_currentChunk;			//the current chunk of thedatabase that we are operating on.  Dictates loading and saving. 
	
	float m_mouseX, m_mouseY;
	bool mouse_LB_Down;


	bool* m_selected;
};
