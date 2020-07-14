#pragma once
#include "MFCRenderFrame.h"
#include "resource.h"
#include "ToolMain.h"
#include "Custom_CEdit.h"
#include "InspectorPreview.h"
#include "SceneObject.h"
#include "MFCInspectorFrame.h"
#include "InputCommands.h"

// InspectorDialogue dialog

class InspectorDialogue : public CDialogEx
{
	DECLARE_DYNAMIC(InspectorDialogue)

public:
	InspectorDialogue(CWnd* pParent = nullptr);   // standard constructor
	virtual ~InspectorDialogue();

	//afx_msg int Create(UINT nIDTemplate, CWnd* pParentWnd);


// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

	void initializeConnection(ToolMain* toolSystem);
	void update();
	void updateSelectionEditText();
	void updateTransformEditText();
	void resetSliders();

	void buildDisplayList(std::vector<SceneObject>* sceneGraph) { m_d3d11Renderer.BuildDisplayList(sceneGraph); }
	void updateDisplayList(SceneObject newSceneObject) { m_d3d11Renderer.updateDisplayList(newSceneObject); }

private:
	ToolMain* m_Tool_System;

	std::vector<DisplayObject>* m_Display_List;
	std::vector<int>* m_selectedObjects;
	InputCommands* m_inputCommands;

	void updateNameEdit();

	InspectorPreview m_d3d11Renderer;
	CChildRender m_DirXView;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog() override;
	
	DECLARE_MESSAGE_MAP()
public:

	bool inputFocus = false;


	CEdit edit_TextBox_ObjectID;

	CButton check_Show_Object;

	Custom_CEdit edit_X_Pos;
	Custom_CEdit edit_Y_Pos;
	Custom_CEdit edit_Z_Pos;

	Custom_CEdit edit_X_Rot;
	Custom_CEdit edit_Y_Rot;
	Custom_CEdit edit_Z_Rot;

	Custom_CEdit edit_X_Scale;
	Custom_CEdit edit_Y_Scale;
	Custom_CEdit edit_Z_Scale;

	CSliderCtrl slider_X_Pos;
	CSliderCtrl slider_Y_Pos;
	CSliderCtrl slider_Z_Pos;

	CSliderCtrl slider_X_Rot;
	CSliderCtrl slider_Y_Rot;
	CSliderCtrl slider_Z_Rot;

	CSliderCtrl slider_X_Scale;
	CSliderCtrl slider_Y_Scale;
	CSliderCtrl slider_Z_Scale;

	afx_msg void OnNMCustomdrawSliderXPos(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderYPos(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderZPos(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderXRot(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderYRot(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderZRot(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderXScale(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderYScale(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderZScale(NMHDR *pNMHDR, LRESULT *pResult);
	
	afx_msg void OnEnSetfocusEditXPos();
	afx_msg void OnEnKillfocusEditXPos();
	afx_msg void OnEnChangeEditXPos();

	afx_msg void OnEnSetfocusEditYPos();
	afx_msg void OnEnKillfocusEditYPos();
	afx_msg void OnEnChangeEditYPos();

	afx_msg void OnEnSetfocusEditZPos();
	afx_msg void OnEnKillfocusEditZPos();
	afx_msg void OnEnChangeEditZPos();

	afx_msg void OnEnSetfocusEditXRot();
	afx_msg void OnEnKillfocusEditXRot();
	afx_msg void OnEnChangeEditXRot();

	afx_msg void OnEnSetfocusEditYRot();
	afx_msg void OnEnKillfocusEditYRot();
	afx_msg void OnEnChangeEditYRot();

	afx_msg void OnEnSetfocusEditZRot();
	afx_msg void OnEnKillfocusEditZRot();
	afx_msg void OnEnChangeEditZRot();

	afx_msg void OnEnSetfocusEditXScale();
	afx_msg void OnEnKillfocusEditXScale();
	afx_msg void OnEnChangeEditXScale();

	afx_msg void OnEnSetfocusEditYScale();
	afx_msg void OnEnKillfocusEditYScale();
	afx_msg void OnEnChangeEditYScale();

	afx_msg void OnEnSetfocusEditZScale();
	afx_msg void OnEnKillfocusEditZScale();
	afx_msg void OnEnChangeEditZScale();
	afx_msg void OnBnClickedCheckVisible();

	CButton check_Visible;
	bool check_focus;
	BOOL check_enableDisable;
	afx_msg void OnBnKillfocusCheckVisible();
	afx_msg void OnBnSetfocusCheckVisible();


	CEdit edit_Set_Name;
	bool edit_Set_Name_IsFocused;
	afx_msg void OnEnChangeEditNameInput();
	afx_msg void OnEnSetfocusEditNameInput();
	afx_msg void OnEnKillfocusEditNameInput();
};
