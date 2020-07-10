// InspectorDialogue.cpp : implementation file
//

#include "stdafx.h"
#include "InspectorDialogue.h"
#include "afxdialogex.h"


// InspectorDialogue dialog

IMPLEMENT_DYNAMIC(InspectorDialogue, CDialogEx)

InspectorDialogue::InspectorDialogue(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

InspectorDialogue::~InspectorDialogue()
{
}

void InspectorDialogue::initializeConnection(ToolMain * toolSystem)
{
	m_Tool_System = toolSystem;
	//m_Tool_System.
}

void InspectorDialogue::update(std::vector<DisplayObject>* display_List, std::vector<int> selectedObjects)
{
	m_Display_List = display_List;
	m_selectedObjects = selectedObjects;

	updateSelectionEditText();

	updateTransformEditText();


	if (m_selectedObjects.size() == 1) {
		
		slider_X_Pos.SetPos(m_Display_List->at(m_selectedObjects[0]).m_X_Pos_Slider_Offset);

		slider_Y_Pos.SetPos(m_Display_List->at(m_selectedObjects[0]).m_Y_Pos_Slider_Offset);

		slider_Z_Pos.SetPos(m_Display_List->at(m_selectedObjects[0]).m_Z_Pos_Slider_Offset);

		slider_X_Rot.SetPos(m_Display_List->at(m_selectedObjects[0]).m_X_Rot_Slider_Offset);

		slider_Y_Rot.SetPos(m_Display_List->at(m_selectedObjects[0]).m_Y_Rot_Slider_Offset);

		slider_Z_Rot.SetPos(m_Display_List->at(m_selectedObjects[0]).m_Z_Rot_Slider_Offset);

		slider_X_Scale.SetPos(m_Display_List->at(m_selectedObjects[0]).m_X_Scale_Slider_Offset);

		slider_Y_Scale.SetPos(m_Display_List->at(m_selectedObjects[0]).m_Y_Scale_Slider_Offset);

		slider_Z_Scale.SetPos(m_Display_List->at(m_selectedObjects[0]).m_Z_Scale_Slider_Offset);
	
	}
	else {
	
		slider_X_Pos.SetPos(0);

		slider_Y_Pos.SetPos(0);

		slider_Z_Pos.SetPos(0);

		slider_X_Rot.SetPos(0);

		slider_Y_Rot.SetPos(0);

		slider_Z_Rot.SetPos(0);

		slider_X_Scale.SetPos(0);

		slider_Y_Scale.SetPos(0);

		slider_Z_Scale.SetPos(0);
	
	}
}

void InspectorDialogue::updateSelectionEditText()
{
	CString outputString;
	std::wstring tempString;

	if (m_selectedObjects.size() > 0) {

		outputString.Empty();

		for (int i = 0; i < m_selectedObjects.size(); i++) {

			if (i == 0) {
				tempString = std::to_wstring(m_selectedObjects[i]);
			}
			else {
				tempString.append(L", ");
				tempString.append(std::to_wstring(m_selectedObjects[i]));
			}

			outputString = tempString.c_str();
		}

		SetDlgItemText(IDC_EDIT_TEXT_ID, outputString);
	}
	else
	{
		outputString.Empty();
		outputString.SetString(_T("Select an Object "));
		SetDlgItemText(IDC_EDIT_TEXT_ID, outputString);
	}
}

void InspectorDialogue::updateTransformEditText()
{

	CString posXString, posYString, posZString;
	CString rotXString, rotYString, rotZString;
	CString scaleXString, scaleYString, scaleZString;

	std::wstring tempString;

	if (m_selectedObjects.size() == 1) {
	
		tempString = std::to_wstring(m_Display_List->at(m_selectedObjects[0]).m_position.x + m_Display_List->at(m_selectedObjects[0]).m_X_Pos_Slider_Offset);
		posXString = tempString.c_str();
	
		tempString = std::to_wstring(m_Display_List->at(m_selectedObjects[0]).m_position.y + m_Display_List->at(m_selectedObjects[0]).m_Y_Pos_Slider_Offset);
		posYString = tempString.c_str();

		tempString = std::to_wstring(m_Display_List->at(m_selectedObjects[0]).m_position.z + m_Display_List->at(m_selectedObjects[0]).m_Z_Pos_Slider_Offset);
		posZString = tempString.c_str();

		tempString = std::to_wstring(m_Display_List->at(m_selectedObjects[0]).m_orientation.x + m_Display_List->at(m_selectedObjects[0]).m_X_Rot_Slider_Offset);
		rotXString = tempString.c_str();

		tempString = std::to_wstring(m_Display_List->at(m_selectedObjects[0]).m_orientation.y + m_Display_List->at(m_selectedObjects[0]).m_Y_Rot_Slider_Offset);
		rotYString = tempString.c_str();

		tempString = std::to_wstring(m_Display_List->at(m_selectedObjects[0]).m_orientation.z + m_Display_List->at(m_selectedObjects[0]).m_Z_Rot_Slider_Offset);
		rotZString = tempString.c_str();

		tempString = std::to_wstring(m_Display_List->at(m_selectedObjects[0]).m_scale.x + m_Display_List->at(m_selectedObjects[0]).m_X_Scale_Slider_Offset);
		scaleXString = tempString.c_str();

		tempString = std::to_wstring(m_Display_List->at(m_selectedObjects[0]).m_scale.y + m_Display_List->at(m_selectedObjects[0]).m_Y_Scale_Slider_Offset);
		scaleYString = tempString.c_str();

		tempString = std::to_wstring(m_Display_List->at(m_selectedObjects[0]).m_scale.z + m_Display_List->at(m_selectedObjects[0]).m_Z_Scale_Slider_Offset);
		scaleZString = tempString.c_str();

	}
	else if (m_selectedObjects.size() > 1) 
	{
	
	}
	else {
	
	
	}

	SetDlgItemText(IDC_EDIT_X_POS, posXString);
	SetDlgItemText(IDC_EDIT_Y_POS, posYString);
	SetDlgItemText(IDC_EDIT_Z_POS, posZString);

	SetDlgItemText(IDC_EDIT_X_ROT, rotXString);
	SetDlgItemText(IDC_EDIT_Y_ROT, rotYString);
	SetDlgItemText(IDC_EDIT_Z_ROT, rotZString);

	SetDlgItemText(IDC_EDIT_X_SCALE, scaleXString);
	SetDlgItemText(IDC_EDIT_Y_SCALE, scaleYString);
	SetDlgItemText(IDC_EDIT_Z_SCALE, scaleZString);

}

void InspectorDialogue::resetSliders()
{
	slider_X_Pos.SetPos(0);
	slider_Y_Pos.SetPos(0);
	slider_Z_Pos.SetPos(0);

	slider_X_Rot.SetPos(0);
	slider_Y_Rot.SetPos(0);
	slider_Z_Rot.SetPos(0);

	slider_X_Scale.SetPos(0);
	slider_Y_Scale.SetPos(0);
	slider_Z_Scale.SetPos(0);

}


void InspectorDialogue::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_TEXT_ID, edit_TextBox_ObjectID);
	DDX_Control(pDX, IDC_CHECK1, check_Show_Object);

	DDX_Control(pDX, IDC_EDIT_X_POS, edit_X_Pos);
	DDX_Control(pDX, IDC_EDIT_Y_POS, edit_Y_Pos);
	DDX_Control(pDX, IDC_EDIT_Z_POS, edit_Z_Pos);

	DDX_Control(pDX, IDC_EDIT_X_ROT, edit_X_Rot);
	DDX_Control(pDX, IDC_EDIT_Y_ROT, edit_Y_Rot);
	DDX_Control(pDX, IDC_EDIT_Z_ROT, edit_Z_Rot);

	DDX_Control(pDX, IDC_EDIT_X_SCALE, edit_X_Scale);
	DDX_Control(pDX, IDC_EDIT_Y_SCALE, edit_Y_Scale);
	DDX_Control(pDX, IDC_EDIT_Z_SCALE, edit_Z_Scale);

	DDX_Control(pDX, IDC_SLIDER_X_POS, slider_X_Pos);
	DDX_Control(pDX, IDC_SLIDER_Y_POS, slider_Y_Pos);
	DDX_Control(pDX, IDC_SLIDER_Z_POS, slider_Z_Pos);

	DDX_Control(pDX, IDC_SLIDER_X_ROT, slider_X_Rot);
	DDX_Control(pDX, IDC_SLIDER_Y_ROT, slider_Y_Rot);
	DDX_Control(pDX, IDC_SLIDER_Z_ROT, slider_Z_Rot);

	DDX_Control(pDX, IDC_SLIDER_X_SCALE, slider_X_Scale);
	DDX_Control(pDX, IDC_SLIDER_Y_SCALE, slider_Y_Scale);
	DDX_Control(pDX, IDC_SLIDER_Z_SCALE, slider_Z_Scale);
}

BOOL InspectorDialogue::OnInitDialog()
{
	//Initialize sliders to sit in the middle for both positive and negative adujustment

	CDialogEx::OnInitDialog();

	slider_X_Pos.SetRange(-200, 200, true);
	slider_X_Pos.SetPos(0);

	slider_Y_Pos.SetRange(-200, 200, true);
	slider_Y_Pos.SetPos(0);

	slider_Z_Pos.SetRange(-200, 200, true);
	slider_Z_Pos.SetPos(0);

	slider_X_Rot.SetRange(-200, 200, true);
	slider_X_Rot.SetPos(0);

	slider_Y_Rot.SetRange(-200, 200, true);
	slider_Y_Rot.SetPos(0);

	slider_Z_Rot.SetRange(-200, 200, true);
	slider_Z_Rot.SetPos(0);

	slider_X_Scale.SetRange(-200, 200, true);
	slider_X_Scale.SetPos(0);

	slider_Y_Scale.SetRange(-200, 200, true);
	slider_Y_Scale.SetPos(0);

	slider_Z_Scale.SetRange(-200, 200, true);
	slider_Z_Scale.SetPos(0);


	return true;
}


BEGIN_MESSAGE_MAP(InspectorDialogue, CDialogEx)

	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_X_POS, &InspectorDialogue::OnNMCustomdrawSliderXPos)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_Y_POS, &InspectorDialogue::OnNMCustomdrawSliderYPos)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_Z_POS, &InspectorDialogue::OnNMCustomdrawSliderZPos)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_X_ROT, &InspectorDialogue::OnNMCustomdrawSliderXRot)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_Y_ROT, &InspectorDialogue::OnNMCustomdrawSliderYRot)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_Z_ROT, &InspectorDialogue::OnNMCustomdrawSliderZRot)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_X_SCALE, &InspectorDialogue::OnNMCustomdrawSliderXScale)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_Y_SCALE, &InspectorDialogue::OnNMCustomdrawSliderYScale)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_Z_SCALE, &InspectorDialogue::OnNMCustomdrawSliderZScale)
END_MESSAGE_MAP()


// InspectorDialogue message handlers


void InspectorDialogue::OnEnChangeEditXPos()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	

	// TODO:  Add your control notification handler code here
}





void InspectorDialogue::OnNMCustomdrawSliderXPos(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here

	if (m_selectedObjects.size() == 1) {
		m_Display_List->at(m_selectedObjects[0]).m_X_Pos_Slider_Offset = slider_X_Pos.GetPos();
	}
	else {
		slider_X_Pos.SetPos(0);
	}

	*pResult = 0;
}


void InspectorDialogue::OnNMCustomdrawSliderYPos(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here

	if (m_selectedObjects.size() == 1) {
		m_Display_List->at(m_selectedObjects[0]).m_Y_Pos_Slider_Offset = slider_Y_Pos.GetPos();
	}
	else {
		slider_Y_Pos.SetPos(0);
	}

	*pResult = 0;
}


void InspectorDialogue::OnNMCustomdrawSliderZPos(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	if (m_selectedObjects.size() == 1) {
		m_Display_List->at(m_selectedObjects[0]).m_Z_Pos_Slider_Offset = slider_Z_Pos.GetPos();
	}
	else {
		slider_Z_Pos.SetPos(0);
	}

	*pResult = 0;
}


void InspectorDialogue::OnNMCustomdrawSliderXRot(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	if (m_selectedObjects.size() == 1) {
		m_Display_List->at(m_selectedObjects[0]).m_X_Rot_Slider_Offset = slider_X_Rot.GetPos();
	}
	else {
		slider_X_Rot.SetPos(0);
	}

	*pResult = 0;
}


void InspectorDialogue::OnNMCustomdrawSliderYRot(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	if (m_selectedObjects.size() == 1) {
		m_Display_List->at(m_selectedObjects[0]).m_Y_Rot_Slider_Offset = slider_Y_Rot.GetPos();
	}
	else {
		slider_Y_Rot.SetPos(0);
	}
	*pResult = 0;
}


void InspectorDialogue::OnNMCustomdrawSliderZRot(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	if (m_selectedObjects.size() == 1) {
		m_Display_List->at(m_selectedObjects[0]).m_Z_Rot_Slider_Offset = slider_Z_Rot.GetPos();
	}
	else {
		slider_Z_Rot.SetPos(0);
	}
	*pResult = 0;
}


void InspectorDialogue::OnNMCustomdrawSliderXScale(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	if (m_selectedObjects.size() == 1) {
		m_Display_List->at(m_selectedObjects[0]).m_X_Scale_Slider_Offset = slider_X_Scale.GetPos();
	}
	else {
		slider_X_Scale.SetPos(0);
	}
	*pResult = 0;
}


void InspectorDialogue::OnNMCustomdrawSliderYScale(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	if (m_selectedObjects.size() == 1) {
		m_Display_List->at(m_selectedObjects[0]).m_Y_Scale_Slider_Offset = slider_Y_Scale.GetPos();
	}
	else {
		slider_Y_Scale.SetPos(0);
	}
	*pResult = 0;
}


void InspectorDialogue::OnNMCustomdrawSliderZScale(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	if (m_selectedObjects.size() == 1) {
		m_Display_List->at(m_selectedObjects[0]).m_Z_Scale_Slider_Offset = slider_Z_Scale.GetPos();
	}
	else {
		slider_Z_Scale.SetPos(0);
	}
	*pResult = 0;
}
