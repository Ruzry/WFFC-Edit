#pragma once

#include "resource.h"
#include "ToolMain.h"
// InspectorDialogue dialog

class InspectorDialogue : public CDialogEx
{
	DECLARE_DYNAMIC(InspectorDialogue)

public:
	InspectorDialogue(CWnd* pParent = nullptr);   // standard constructor
	virtual ~InspectorDialogue();




// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

	void initializeConnection(ToolMain* toolSystem);
	void update(std::vector<DisplayObject>* display_List, std::vector<int> selectedObjects);
	void updateSelectionEditText();
	void updateTransformEditText();
	void resetSliders();


private:
	ToolMain* m_Tool_System;

	std::vector<DisplayObject>* m_Display_List;
	std::vector<int> m_selectedObjects;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog() override;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEditXPos();




	CEdit edit_TextBox_ObjectID;

	CButton check_Show_Object;

	CEdit edit_X_Pos;
	CEdit edit_Y_Pos;
	CEdit edit_Z_Pos;

	CEdit edit_X_Rot;
	CEdit edit_Y_Rot;
	CEdit edit_Z_Rot;

	CEdit edit_X_Scale;
	CEdit edit_Y_Scale;
	CEdit edit_Z_Scale;

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
};
